// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWCharacter.h"

#include "FWGameInstance.h"
#include "Character/FWCharacterMovementComponent.h"
#include "Controller/FWController.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Gameplay/Interactible/InteractibleActor.h"
#include "Gameplay/Component/InteractionManager.h"
#include "Gameplay/Component/StablePositionUpdater.h"
#include "Gameplay/Component/ItemManagerComponent.h"
#include "Gameplay/Component/KeyInventoryComponent.h"
#include "Gameplay/Component/PlayerStatsComponent.h"
#include "Gameplay/Component/WeaponManager.h"
#include "Save/FWSaveGame.h"
#include "Serialization/MemoryReader.h"

AFWCharacter::AFWCharacter(FObjectInitializer const &ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UFWCharacterMovementComponent>(CharacterMovementComponentName))
{
	FWMovementComponent = Cast<UFWCharacterMovementComponent>(Super::GetMovementComponent());
	PlayerStats = CreateDefaultSubobject<UPlayerStatsComponent>(TEXT("PlayerStatsManager"));
	StablePositionUpdater = CreateDefaultSubobject<UStablePositionUpdater>(TEXT("StablePosition"));
	ItemManager = CreateDefaultSubobject<UItemManagerComponent>(TEXT("ItemManager"));
	KeyManager = CreateDefaultSubobject<UKeyInventoryComponent>(TEXT("KeyManager"));
	WeaponManager = CreateDefaultSubobject<UWeaponManager>(TEXT("WeaponManager"));
	InteractionManager = CreateDefaultSubobject<UInteractionManagerComponent>(TEXT("InteractionManager"));

	GetCharacterMovement()->SetIsReplicated(true);
	bReplicates = true;
}

void AFWCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

void AFWCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (FWMovementComponent)
	{
		FWMovementComponent->GetNavAgentPropertiesRef().bCanCrouch = true;
		FWMovementComponent->GetNavAgentPropertiesRef().bCanJump = true;
	}

	if (!FWGameInstance)
		FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());

	if (!FWController)
	{
		FWController = Cast<AFWController>(GetController());
	}

	Level = GetWorld()->GetName();

	if (FWGameInstance && FWGameInstance.Get()->CurrentLoadedSave)
	{
		FMemoryReader PlayerReader = FMemoryReader(FWGameInstance->CurrentLoadedSave->PlayerData);
		FArchive Ar = FArchive(PlayerReader);
		Serialize(Ar);
	}

	SetActorTransform(StablePositionUpdater->StablePosition, false, nullptr, ETeleportType::TeleportPhysics);
}

void AFWCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AFWCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	if (FWGameInstance && FWGameInstance->CurrentLoadedSave)
	{
		FWGameInstance->CurrentLoadedSave->PlayerLevel = Level;
		FWGameInstance->CurrentLoadedSave->bHasSavedLevel = true;
		
		FWGameInstance->SetShouldSaveGame(true);
	}
}

FCollisionQueryParams AFWCharacter::GetIgnoreCharacterParams()
{
	FCollisionQueryParams Params;

	TArray<AActor*> IgnoreActors;
	GetAllChildActors(IgnoreActors);
	Params.AddIgnoredActors(IgnoreActors);
	Params.AddIgnoredActor(this);

	return Params;
}

float AFWCharacter::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (PlayerStats)
	{
		PlayerStats.Get()->DoDamage(Damage);
	}

	FVector DamageCauserPos = DamageCauser->GetActorLocation();
	FVector SelfLocation = GetActorLocation();

	FVector Difference = SelfLocation - DamageCauserPos;
	Difference.Normalize();

	Difference = Difference * Damage * KnockbackMultiplier;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Damage: %f"), Damage));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Knockback: %s"), *Difference.ToString()));
	}
	LaunchCharacterServer(Difference, false, false);

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AFWCharacter::Interact()
{
	AActor * CurrentInteractible = InteractionManager.Get()->GetCurrentInteractible();
	if (CurrentInteractible && CurrentInteractible->Implements<UInteractableActor>())
	{
		IInteractableActor *Interactible = Cast<IInteractableActor>(CurrentInteractible);
		Interactible->Interact(this);
	}
}

void AFWCharacter::LaunchCharacterServer_Implementation(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}

void AFWCharacter::AddLookInput(const FVector2D& Look)
{
	Super::AddControllerYawInput(Look.X);
	Super::AddControllerPitchInput(Look.Y);
}

void AFWCharacter::AddMovementInput(const FVector2D& Move)
{
	AddMovementInput(GetActorForwardVector(), Move.X, false);
	AddMovementInput(GetActorRightVector(), Move.Y, false);
}

void AFWCharacter::SprintPressed() const
{
	FWMovementComponent->SprintPressed();
}

void AFWCharacter::SprintReleased() const
{
	FWMovementComponent->SprintReleassed();
}

void AFWCharacter::Fire()
{
	WeaponManager.Get()->StartFire();
}

void AFWCharacter::StopFire()
{
	WeaponManager.Get()->EndFire();
}

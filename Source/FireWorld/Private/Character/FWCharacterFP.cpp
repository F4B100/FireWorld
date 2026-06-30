// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWCharacterFP.h"

#include "FWGlobalGI.h"
#include "Character/FWCharacterMovementComponent.h"
#include "Gameplay/Component/PlayerStatsComponent.h"
#include "Gameplay/Component/Weapon.h"
#include "Save/FWSaveGame.h"

void AFWCharacterFP::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

void AFWCharacterFP::BeginPlay()
{
	Super::BeginPlay();

	if (FWMovementComponent)
	{
		FWMovementComponent->GetNavAgentPropertiesRef().bCanCrouch = true;
		FWMovementComponent->GetNavAgentPropertiesRef().bCanJump = true;
	}

	if (!GameInstance)
		GameInstance = Cast<UFWGlobalGI>(GetGameInstance());
	
	Level = GetWorld()->GetName();
}

void AFWCharacterFP::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

void AFWCharacterFP::BeginDestroy()
{
	Super::BeginDestroy();

	if (GameInstance && GameInstance->CurrentLoadedSave)
	{
		GameInstance->CurrentLoadedSave->PlayerLevel = Level;
		GameInstance->CurrentLoadedSave->bHasSavedLevel = true;
		
		GameInstance->SaveGame();
	}
}

FCollisionQueryParams AFWCharacterFP::GetIgnoreCharacterParams()
{
	FCollisionQueryParams Params;

	TArray<AActor*> IgnoreActors;
	GetAllChildActors(IgnoreActors);
	Params.AddIgnoredActors(IgnoreActors);
	Params.AddIgnoredActor(this);

	return Params;
}

float AFWCharacterFP::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
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

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AFWCharacterFP::LaunchCharacterServer_Implementation(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}

AFWCharacterFP::AFWCharacterFP(FObjectInitializer const &ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UFWCharacterMovementComponent>(CharacterMovementComponentName))
{
	FWMovementComponent = Cast<UFWCharacterMovementComponent>(Super::GetMovementComponent());

	GetCharacterMovement()->SetIsReplicated(true);
	bReplicates = true;
}

void AFWCharacterFP::AddLookInput(const FVector2D& Look)
{
	Super::AddControllerYawInput(Look.X);
	Super::AddControllerPitchInput(Look.Y);
}

void AFWCharacterFP::AddMovementInput(const FVector2D& Move)
{
	AddMovementInput(GetActorForwardVector(), Move.X, false);
	AddMovementInput(GetActorRightVector(), Move.Y, false);
}

void AFWCharacterFP::SprintPressed() const
{
	FWMovementComponent->SprintPressed();
}

void AFWCharacterFP::SprintReleased() const
{
	FWMovementComponent->SprintReleassed();
}

void AFWCharacterFP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFWCharacterFP::Fire()
{
	UWeapon *weapon = GetComponentByClass<UWeapon>();
	if (weapon)
	{
		weapon->bWantsToFire = true;
	}
}

void AFWCharacterFP::StopFire()
{
	UWeapon *weapon = GetComponentByClass<UWeapon>();
	if (weapon)
	{
		weapon->bWantsToFire = false;
	}
}

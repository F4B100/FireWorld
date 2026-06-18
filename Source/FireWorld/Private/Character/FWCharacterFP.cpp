// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWCharacterFP.h"

#include "FWGlobalGI.h"
#include "Character/FWCharacterMovementComponent.h"
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

	if (GameInstance)
	{
		GameInstance->CurrentLoadedSave->PlayerLevel = Level;
		GameInstance->CurrentLoadedSave->bHasSavedLevel = true;
		
		GameInstance->SaveGame();
	}
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
	FWMovementComponent->SprintReleased();
}

void AFWCharacterFP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

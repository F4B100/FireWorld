// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWPlayerCameraManagerFP.h"

#include "Character/FWCharacterFP.h"
#include "Character/FWCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AFWPlayerCameraManagerFP::AFWPlayerCameraManagerFP()
{
}

void AFWPlayerCameraManagerFP::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);
	if (AFWCharacterFP *CharacterFP = Cast<AFWCharacterFP>(GetOwningPlayerController()->GetCharacter()))
	{
		UFWCharacterMovementComponent *MovementComponent = CharacterFP->GetFWMovementComponent();
		FVector TargetCrouchOffset = FVector(
			0.0f,
			0.0f,
			MovementComponent->GetCrouchedHalfHeight() - CharacterFP->GetClass()->GetDefaultObject<ACharacter>()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
		);
		FVector Offset = FMath::InterpEaseInOut(
			FVector::Zero(),
			TargetCrouchOffset,
			FMath::Clamp(
				CrouchInterpolateTime / CrouchInterpolateDuration, 0.0f, 1.0f
			),
			1.5f
		);

		if (MovementComponent->IsCrouching())
		{
			CrouchInterpolateTime = FMath::Clamp(CrouchInterpolateTime + DeltaTime, 0.0, CrouchInterpolateDuration);
			Offset -= TargetCrouchOffset;
		}
		else
		{
			CrouchInterpolateTime = FMath::Clamp(CrouchInterpolateTime - DeltaTime, 0.0, CrouchInterpolateDuration);
		}

		if (MovementComponent->IsMovingOnGround())
		{
			OutVT.POV.Location += Offset;
		}
	}
}

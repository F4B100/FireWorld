// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWPlayerCameraManagerFP.h"

#include "Character/FWCharacter.h"
#include "Character/FWCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AFWPlayerCameraManagerFP::AFWPlayerCameraManagerFP()
{
}

void AFWPlayerCameraManagerFP::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);
	if (AFWCharacter *CharacterFP = Cast<AFWCharacter>(GetOwningPlayerController()->GetCharacter()))
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
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(13123131, 1.0f, FColor::Yellow, FString::Printf(TEXT("ViewBoobingInterpolateTime: %f\n"), ViewBoobingInterpolateTime));
			}
			Offset.Z += FMath::InterpEaseInOut(
				Offset.Z,
				Offset.Z + ViewBoobingMagntude,
				FMath::Sin(ViewBoobingInterpolateTime),
				1.5f);
			ViewBoobingInterpolateTime += DeltaTime;
			if (ViewBoobingInterpolateTime > PI)
			{
				ViewBoobingInterpolateTime = 0.0f;
			}
		} else
		{
			ViewBoobingInterpolateTime = 0.0f;
		}

		if (MovementComponent->IsMovingOnGround())
		{
			OutVT.POV.Location += Offset;
		}
	}
}

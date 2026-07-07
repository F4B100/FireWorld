// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWCharacterMovementComponent.h"

#include <string>

#include "Character/FWCharacter.h"
#include "Components/CapsuleComponent.h"

void UFWCharacterMovementComponent::FSavedMove_FW::Clear()
{
	FSavedMove_Character::Clear();
	
	Saved_bWantsToSprint = 0;
	Saved_bPrevWantsToCrouch = 0;
	Saved_bJustLanded = 0;
}

void UFWCharacterMovementComponent::FSavedMove_FW::SetMoveFor(ACharacter* C, float InDeltaTime, const FVector& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);
	
	TObjectPtr<UFWCharacterMovementComponent> character = Cast<UFWCharacterMovementComponent>(C->GetCharacterMovement());
	
	Saved_bWantsToSprint = character->Safe_bWantsToSprint;
	Saved_bPrevWantsToCrouch = character->Safe_bPrevWantsToCrouch;
	Saved_bJustLanded = character->Safe_bJustLanded;
}

void UFWCharacterMovementComponent::FSavedMove_FW::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);
	
	TObjectPtr<UFWCharacterMovementComponent> character = Cast<UFWCharacterMovementComponent>(C->GetCharacterMovement());
	
	character->Safe_bWantsToSprint = Saved_bWantsToSprint;
	character->Safe_bPrevWantsToCrouch = Saved_bPrevWantsToCrouch;
	character->Safe_bJustLanded = Saved_bJustLanded;
}

bool UFWCharacterMovementComponent::FSavedMove_FW::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	FSavedMove_FW* NewFWMove = static_cast<FSavedMove_FW*>(NewMove.Get());

	if (NewFWMove->Saved_bWantsToSprint != Saved_bWantsToSprint) return false;
	if (NewFWMove->Saved_bPrevWantsToCrouch != Saved_bPrevWantsToCrouch) return false;
	if (NewFWMove->Saved_bJustLanded != Saved_bJustLanded) return false;

	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

uint8 UFWCharacterMovementComponent::FSavedMove_FW::GetCompressedFlags() const
{
	uint8_t prevResult = FSavedMove_Character::GetCompressedFlags();
	if (Saved_bWantsToSprint)
	{
		prevResult |= FLAG_Custom_0;
	}
	return prevResult;
}

UFWCharacterMovementComponent::FNetworkPredictionData_Client_FW::FNetworkPredictionData_Client_FW(
	const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{
}

FSavedMovePtr UFWCharacterMovementComponent::FNetworkPredictionData_Client_FW::AllocateNewMove()
{
	return MakeShared<FSavedMove_FW>();
}

UFWCharacterMovementComponent::UFWCharacterMovementComponent()
{
}

FNetworkPredictionData_Client* UFWCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if (ClientPredictionData == nullptr)
	{
		UFWCharacterMovementComponent *MutableThis = const_cast<UFWCharacterMovementComponent *>(this);
		
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_FW(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.0f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.0f;
	}
	return ClientPredictionData;
}

void UFWCharacterMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = true;
}

void UFWCharacterMovementComponent::SprintReleassed()
{
	Safe_bWantsToSprint = false;
}

void UFWCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	FWCharacterOwner = Cast<AFWCharacter>(GetOwner());
}

bool UFWCharacterMovementComponent::IsCustomMovementMode(FWCharacterMovementMode InMovementMode) const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == InMovementMode;
}

bool UFWCharacterMovementComponent::IsMovingOnGround() const
{
	return Super::IsMovingOnGround() || IsCustomMovementMode(CMOVE_SLIDE);
}

bool UFWCharacterMovementComponent::CanCrouchInCurrentState() const
{
	return Super::CanCrouchInCurrentState() && IsMovingOnGround();
}

void UFWCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
                                                      const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (MovementMode == MOVE_Walking)
	{
		if (Safe_bWantsToSprint)
		{
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
		} else
		{
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}
	}

	Safe_bPrevWantsToCrouch = bWantsToCrouch;
	if (Safe_bPrevWantsToCrouch && !bWantsToCrouch)
	{
		Safe_bPrevWantsToCrouch = false;
	}
}

void UFWCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	if (MovementMode == MOVE_Walking && !bWantsToCrouch && Safe_bPrevWantsToCrouch)
	{
		FHitResult PotencialSlideSurface;
		if (Velocity.SizeSquared() > pow(Slide_MinSpeed, 2) && GetSlideSurface(PotencialSlideSurface))
		{
			EnterSlide();
		}
	}

	if (IsCustomMovementMode(CMOVE_SLIDE) && !bWantsToCrouch)
	{
		ExitSlide();
	}

	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

FVector UFWCharacterMovementComponent::Accelerate(FVector wishdir, float wishspeed, float accel, float DeltaTime)
{
	float currentspeed = FVector::DotProduct(Velocity, wishdir);
	float addspeed = wishspeed - currentspeed;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(314512,15.0f, FColor::Yellow,FString::Printf(TEXT("addSpeed: %f|angle: %f\n"), addspeed, Velocity.CosineAngle2D(wishdir)));
	}
	if (addspeed <= 0) return Velocity;

	float accelspeed = FMath::Min(accel * wishspeed * DeltaTime, addspeed);
	return Velocity + accelspeed * wishdir;
}

FVector UFWCharacterMovementComponent::ApplyFriction(float DeltaTime)
{
	float speed = Velocity.Size2D();
	if (speed < 1.0f) return Velocity;

	float control = FMath::Max(speed, Ground_StopSpeed);
	float drop = control * Ground_Friction * DeltaTime;
	float scale = FMath::Max(speed - drop, 0.0f) / speed;

	return FVector(Velocity.X * scale, Velocity.Y * scale, Velocity.Z);
}

void UFWCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	// detect landing to set the bhop window
	if (MovementMode == MOVE_Walking && PreviousMovementMode == MOVE_Falling)
	{
		Safe_bJustLanded = true;
	}
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void UFWCharacterMovementComponent::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
	if (IsCustomMovementMode(CMOVE_SLIDE))
	{
		Super::CalcVelocity(DeltaTime, Friction, bFluid, BrakingDeceleration);
		return;
	}
	if (!HasValidData() || HasAnimRootMotion() || DeltaTime < MIN_TICK_TIME || (CharacterOwner && CharacterOwner->GetLocalRole() == ROLE_SimulatedProxy && !bWasSimulatingRootMotion))
	{
		return;
	}

	if (MovementMode == MOVE_Walking)
	{
		if (bWantsToCrouch)
			Safe_bJustLanded = false;
		else
			Velocity = ApplyFriction(DeltaTime);

		if (Safe_bPrevWantsToCrouch)
		{
			Crouch();
		}

		const FVector Wishdir = Acceleration.GetSafeNormal2D();
		Velocity = Accelerate(Wishdir, MaxWalkSpeed, Ground_Accelerate, DeltaTime);
		if (PendingLaunchVelocity != FVector::ZeroVector)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("WishDir: %s"), *PendingLaunchVelocity.ToString()));
			}
			Velocity += PendingLaunchVelocity;
		}
		return;
	}

	if (MovementMode == MOVE_Falling)
	{
		if (bWantsToCrouch)
		{
			Crouch();
		}

		const FVector Wishdir = Acceleration.GetSafeNormal2D();
		Velocity = Accelerate(Wishdir, Air_MaxSpeed, Air_Accelerate, DeltaTime);
		return;
	}

	Super::CalcVelocity(DeltaTime, Friction, bFluid, BrakingDeceleration);
}

void UFWCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if (MovementMode == MOVE_Custom)
	{
		switch (CustomMovementMode)
		{
		case CMOVE_SLIDE:
			PhysSlide(deltaTime, Iterations);
			break;
		default:
			UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"));
		}
	}
	Super::PhysCustom(deltaTime, Iterations);
}

void UFWCharacterMovementComponent::EnterSlide()
{
	bWantsToCrouch = true;
	Velocity += Velocity.GetSafeNormal2D() * Slide_EnterImpulse;
	SetMovementMode(MOVE_Custom, CMOVE_SLIDE);
}

void UFWCharacterMovementComponent::ExitSlide()
{
	bWantsToCrouch = false;

	FQuat NewRotation = FRotationMatrix::MakeFromXZ(UpdatedComponent->GetForwardVector().GetSafeNormal2D(), FVector::UpVector).ToQuat();
	FHitResult Hit;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, true, Hit);
	SetMovementMode(MOVE_Walking);
}

void UFWCharacterMovementComponent::PhysSlide(float DeltaTime, int32 Iterations)
{
	if (DeltaTime < MIN_TICK_TIME)
	{
		return;
	}

	RestorePreAdditiveRootMotionVelocity();

	FHitResult SurfaceHit;
	bool test = GetSlideSurface(SurfaceHit);
	bool test2 = Velocity.SizeSquared() < pow(Slide_MinSpeed, 2);
	if (!test || test2)
	{
		ExitSlide();
		StartNewPhysics(DeltaTime, Iterations);
		return;
	}

	Velocity += Slide_GravityForce * FVector::DownVector * DeltaTime;

	if (FMath::Abs(FVector::DotProduct(Acceleration.GetSafeNormal(), UpdatedComponent->GetRightVector())) > 0.5f)
	{
		Acceleration = Acceleration.ProjectOnTo(UpdatedComponent->GetRightVector());
	}
	else
	{
		Acceleration = FVector::ZeroVector;
	}

	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		CalcVelocity(DeltaTime, Slide_Friction, true, GetMaxBrakingDeceleration());
	}
	ApplyRootMotionToVelocity(DeltaTime);

	Iterations++;
	bJustTeleported = false;

	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	FQuat OldRotation = UpdatedComponent->GetComponentRotation().Quaternion();
	FHitResult Hit(1.0f);
	FVector Adjusted = Velocity * DeltaTime;
	FVector VelPlaneDir = FVector::VectorPlaneProject(Velocity, SurfaceHit.Normal).GetSafeNormal();
	FQuat NewRotation = FRotationMatrix::MakeFromXZ(VelPlaneDir, SurfaceHit.Normal).ToQuat();
	SafeMoveUpdatedComponent(Adjusted, NewRotation, true, Hit);

	if (Hit.Time < 1.0f)
	{
		HandleImpact(Hit, DeltaTime, Adjusted);
		SlideAlongSurface(Adjusted, 1.0f - Hit.Time, Hit.Normal, Hit, true);
	}

	FHitResult NewSurfaceHit;
	if (!GetSlideSurface(NewSurfaceHit) || Velocity.SizeSquared() < pow(Slide_MinSpeed, 2))
	{
		ExitSlide();
	}

	if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / DeltaTime;
	}
}

bool UFWCharacterMovementComponent::GetSlideSurface(FHitResult& HitResult)
{
	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector End = Start + CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.0f * FVector::DownVector;
	FName ProfileName = TEXT("BlockAll");
	return GetWorld()->LineTraceSingleByProfile(HitResult, Start, End, ProfileName, FWCharacterOwner.Get()->GetIgnoreCharacterParams());
}

void UFWCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Safe_bWantsToSprint = (Flags & FSavedMove_FW::FLAG_Custom_0) != 0;
	Super::UpdateFromCompressedFlags(Flags);
}

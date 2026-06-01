// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWCharacterMovementComponent.h"

#include "Character/FWCharacterFP.h"

void UFWCharacterMovementComponent::FSavedMove_FW::Clear()
{
	FSavedMove_Character::Clear();
	
	SavedWantsToSprint = 0;
}

void UFWCharacterMovementComponent::FSavedMove_FW::SetMoveFor(ACharacter* C, float InDeltaTime, const FVector& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);
	
	TObjectPtr<UFWCharacterMovementComponent> character = Cast<UFWCharacterMovementComponent>(C->GetCharacterMovement());
	
	SavedWantsToSprint = character->bSafeWantsToSprint;
}

void UFWCharacterMovementComponent::FSavedMove_FW::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);
	
	TObjectPtr<UFWCharacterMovementComponent> character = Cast<UFWCharacterMovementComponent>(C->GetCharacterMovement());
	
	SavedWantsToSprint = character->bSafeWantsToSprint;
}

bool UFWCharacterMovementComponent::FSavedMove_FW::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter,
                                                                  float MaxDelta) const
{
	FSavedMove_FW *NewFWMove = static_cast<FSavedMove_FW *>(NewMove.Get());

	if (NewFWMove->SavedWantsToSprint != this->SavedWantsToSprint)
	{
		return false;
	}
	
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

uint8 UFWCharacterMovementComponent::FSavedMove_FW::GetCompressedFlags() const
{
	uint8_t prevResult = FSavedMove_Character::GetCompressedFlags();
	if (SavedWantsToSprint)
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
	return FSavedMovePtr(new FSavedMove_FW);
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
	bSafeWantsToSprint = true;
}

void UFWCharacterMovementComponent::SprintReleassed()
{
	bSafeWantsToSprint = false;
}

void UFWCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
	const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (MovementMode == MOVE_Walking)
	{
		if (bSafeWantsToSprint)
		{
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
		} else
		{
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}
	}
}

void UFWCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	bSafeWantsToSprint = (Flags & FSavedMove_FW::FLAG_Custom_0) != 0;
	Super::UpdateFromCompressedFlags(Flags);
}

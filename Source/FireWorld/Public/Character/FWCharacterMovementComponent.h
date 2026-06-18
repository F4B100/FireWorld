// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FWCharacterMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UFWCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	class FSavedMove_FW : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;
		
		uint8_t SavedWantsToSprint:1;
	public:
		explicit FSavedMove_FW() : SavedWantsToSprint(0)
		{
		}

		explicit FSavedMove_FW(uint8_t SavedWantsToSprint)
			: SavedWantsToSprint(SavedWantsToSprint)
		{
		}

		FSavedMove_FW(const FSavedMove_Character& SavedMove_Character, uint8_t SavedWantsToSprint)
			: FSavedMove_Character(SavedMove_Character),
			  SavedWantsToSprint(SavedWantsToSprint)
		{
		}

		FSavedMove_FW(FSavedMove_Character&& SavedMove_Character, uint8_t SavedWantsToSprint)
			: FSavedMove_Character(SavedMove_Character),
			  SavedWantsToSprint(SavedWantsToSprint)
		{
		}

		virtual void Clear() override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, const FVector& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void PrepMoveFor(ACharacter* C) override;
		virtual uint8 GetCompressedFlags() const override;
	};
	
	class FNetworkPredictionData_Client_FW : public FNetworkPredictionData_Client_Character
	{
	public:
		typedef FNetworkPredictionData_Client_Character Super;
		FNetworkPredictionData_Client_FW(const UCharacterMovementComponent& ClientMovement);
		
		virtual FSavedMovePtr AllocateNewMove() override;
	};
	
	UPROPERTY(EditDefaultsOnly)
	float Sprint_MaxWalkSpeed;
	UPROPERTY(EditDefaultsOnly)
	float Walk_MaxWalkSpeed;

	bool bSafeWantsToSprint;
	
public:
	UFWCharacterMovementComponent();
	
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	
	UFUNCTION(BlueprintCallable)
	void SprintPressed();
	UFUNCTION(BlueprintCallable)
	void SprintReleassed();

	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;

protected:
	virtual void PhysWalking(float deltaTime, int32 Iterations) override;

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
};

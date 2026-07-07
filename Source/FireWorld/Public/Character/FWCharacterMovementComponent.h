// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FWCharacterMovementComponent.generated.h"

class AFWCharacter;

UENUM(BlueprintType)
enum FWCharacterMovementMode
{
	CMOVE_NONE UMETA(Hidden),
	CMOVE_SLIDE UMETA(DisplayName = "Slide"),
	CMOVE_MAX UMETA(DisplayName = "Max")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UFWCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	class FSavedMove_FW : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		// Flags
		uint8_t Saved_bWantsToSprint:1;

		uint8_t Saved_bPrevWantsToCrouch:1;
		uint8_t Saved_bJustLanded:1;
	public:
		explicit FSavedMove_FW() : Saved_bWantsToSprint(0)
		{
		}

		explicit FSavedMove_FW(uint8_t SavedWantsToSprint)
			: Saved_bWantsToSprint(SavedWantsToSprint)
		{
		}

		FSavedMove_FW(const FSavedMove_Character& SavedMove_Character, uint8_t SavedWantsToSprint)
			: FSavedMove_Character(SavedMove_Character),
			  Saved_bWantsToSprint(SavedWantsToSprint)
		{
		}

		FSavedMove_FW(FSavedMove_Character&& SavedMove_Character, uint8_t SavedWantsToSprint)
			: FSavedMove_Character(SavedMove_Character),
			  Saved_bWantsToSprint(SavedWantsToSprint)
		{
		}

		virtual void Clear() override;
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, const FVector& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
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

	// Ground PARAMS
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Ground")
	float Sprint_MaxWalkSpeed = 900.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Ground")
	float Walk_MaxWalkSpeed = 600.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Ground")
	float Ground_Accelerate = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Ground")
	float Ground_Friction = 4.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Ground")
	float Ground_StopSpeed = 100.0f;

	// Air Params
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Air")
	float Air_Accelerate = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Air")
	float Air_MaxSpeed = 30.0f;

	// SLIDE PARAMS
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Slide")
	float Slide_MinSpeed = 350.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Slide")
	float Slide_EnterImpulse = 500.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Slide")
	float Slide_GravityForce = 5000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Slide")
	float Slide_Friction = 1.3f;

	UPROPERTY(Transient)
	TObjectPtr<AFWCharacter> FWCharacterOwner;

	bool Safe_bWantsToSprint;
	bool Safe_bPrevWantsToCrouch;
	bool Safe_bJustLanded;

public:
	UFWCharacterMovementComponent();
	
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	
	UFUNCTION(BlueprintCallable)
	void SprintPressed();
	UFUNCTION(BlueprintCallable)
	void SprintReleassed();

	virtual void InitializeComponent() override;

	UFUNCTION(Blueprintable)
	bool IsCustomMovementMode(FWCharacterMovementMode InMovementMode) const;


	virtual bool IsMovingOnGround() const override;
	virtual bool CanCrouchInCurrentState() const override;

protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;

	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	FVector Accelerate(FVector wishdir, float wishspeed, float accel, float DeltaTime);
	FVector ApplyFriction(float DeltaTime);

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
private:
	void EnterSlide();
	void ExitSlide();
	void PhysSlide(float DeltaTime,int32 Iterations);
	bool GetSlideSurface(FHitResult& HitResult);
};

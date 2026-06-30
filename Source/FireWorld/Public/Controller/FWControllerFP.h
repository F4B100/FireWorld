// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "FWControllerFP.generated.h"

struct FInputActionValue;
class AFWCharacterFP;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable)
class FIREWORLD_API AFWControllerFP : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> JumpAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> LookAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> SprintAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> CrouchAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> ShootAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Input")
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Character")
	TObjectPtr<AFWCharacterFP> FWCharacter = nullptr;
	
	AFWControllerFP();

protected:
	void Start(const FInputActionValue& InputActionValue);
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* APawn) override;

	void OnJump();
	void SprintDown();
	void SprintUp();
	void HandleCrouch(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
	void StartShooting(const FInputActionValue& InputActionValue);
	void StopShooting(const FInputActionValue& InputActionValue);
public:
	virtual void Tick(float DeltaTime) override;
	virtual void AcknowledgePossession(APawn* P) override;
};

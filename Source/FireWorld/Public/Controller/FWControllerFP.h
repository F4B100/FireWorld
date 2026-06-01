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
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Input")
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Character")
	TObjectPtr<AFWCharacterFP> FWCharacter = nullptr;
	
	AFWControllerFP();
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* APawn) override;

	void OnJump();
	void SprintDown();
	void SprintUp();
	void HandleCrouch(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
public:
	virtual void Tick(float DeltaTime) override;
	virtual void AcknowledgePossession(APawn* P) override;
};

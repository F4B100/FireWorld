// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FWCharacterFP.generated.h"

class UFWGlobalGI;
class UFWCharacterMovementComponent;
class UInputAction;

UCLASS(Blueprintable)
class FIREWORLD_API AFWCharacterFP : public ACharacter
{
	GENERATED_BODY()
public:
	explicit AFWCharacterFP(FObjectInitializer const &);
	
	void AddLookInput(const FVector2D& Look);
	void AddMovementInput(const FVector2D& Move);
	
	void SprintPressed() const;
	void SprintReleased() const;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	TObjectPtr<UFWCharacterMovementComponent> FWMovementComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Bool)
	bool bShouldReadSaveData = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UFWGlobalGI> GameInstance = nullptr;
	
	FString Level = FString("");
	
	TObjectPtr<UFWCharacterMovementComponent> GetFWMovementComponent() {return FWMovementComponent;}
	
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce = false) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginDestroy() override;
};

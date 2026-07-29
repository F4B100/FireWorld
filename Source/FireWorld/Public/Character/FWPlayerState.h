// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FWPlayerState.generated.h"

class UFWGameInstance;
class UItemManagerComponent;
class UFWItem;
/**
 * 
 */
UCLASS()
class FIREWORLD_API AFWPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;
	UPROPERTY()
	TObjectPtr<UItemManagerComponent> ItemManagerComponent = nullptr;

	AFWPlayerState();
public:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	UItemManagerComponent* GetItemManager();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Gameplay/Component/SavedInventory.h"
#include "FWSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	bool bHasPlayerData = false;
	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	TArray<uint8> PlayerData = TArray<uint8>();
	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	FString PlayerLevel = FString();
	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	bool bHasSavedLevel = false;

	UPROPERTY(BlueprintReadWrite, Category = "Locations")
	TMap<FString, FTransform> SavedActorTransforms = TMap<FString, FTransform>();

	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	FSavedInventory SavedInventory = FSavedInventory();

};

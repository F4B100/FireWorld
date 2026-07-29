// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Gameplay/Component/SavedInventory.h"
#include "FWSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSerializedActorData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<uint8> Data;
};

UENUM(BlueprintType)
enum EGameDificulty
{
	GDIFICULTY_NONE UMETA(Hidden),
	GDIFICULTY_EASY UMETA(DisplayName = "Easy"),
	GDIFICULTY_NORMAL UMETA(DisplayName = "Normal"),
	GDIFICULTY_HARD UMETA(DisplayName = "Hard")
};

/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	bool bHasPlayerData = false;
	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	TArray<uint8> PlayerData = TArray<uint8>();

	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	FSavedInventory SavedInventory;

	UPROPERTY(BlueprintReadOnly, Category = "Locations")
	TMap<FString, FSerializedActorData> SavedActorData;

	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	TEnumAsByte<EGameDificulty> Dificulty = GDIFICULTY_NORMAL;
};

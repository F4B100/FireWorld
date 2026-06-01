// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "FWSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Player Stats")
	float PlayerHealth = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Locations")
	TMap<FString, FTransform> SavedActorTransforms = TMap<FString, FTransform>();
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	FString PlayerLevel = FString();
	UPROPERTY(BlueprintReadOnly, Category = "Player Save")
	bool bHasSavedLevel = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Inventory")
	TMap<FString, FString> PlayerInventory = TMap<FString, FString>();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FWSaveNames.generated.h"

/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWSaveNames : public USaveGame
{
	public:
	UPROPERTY(BlueprintReadOnly, Category = "Save")
	TSet<FString> SaveNames;
	private:
	GENERATED_BODY()
};

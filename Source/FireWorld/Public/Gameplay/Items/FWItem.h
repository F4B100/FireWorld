// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save/FWSaveGame.h"
#include "Styling/SlateBrush.h"
#include "UObject/Object.h"
#include "FWItem.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWItem : public UObject
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	FName ItemName = FName("No Name");
	UPROPERTY(EditDefaultsOnly)
	FSlateBrush ItemBrush;

public:
	UFWItem();

	UFUNCTION(BlueprintCallable)
	FName& GetItemName() {return ItemName;}
	UFUNCTION(BlueprintCallable)
	FSlateBrush& GetItemBrush() {return ItemBrush;}

	UFUNCTION(BlueprintCallable)
	virtual void CreateSavedItem(FSavedItem& SavedItem);

	virtual void Serialize(FArchive& Ar) override;
};

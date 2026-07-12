// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save/FWSaveGame.h"
#include "UObject/Object.h"
#include "FWItem.generated.h"

/**
 *
 */
UCLASS(ClassGroup=(Custom), Blueprintable)
class FIREWORLD_API UFWItem : public UObject
{
	GENERATED_BODY()
	public:
	FName ItemName = FName("No Name");

	virtual void CreateSavedItem(FSavedItem& SavedItem);
	void Deserialize(TArray<uint8> Data);
	virtual void Serialize(FArchive& Ar) override;
};

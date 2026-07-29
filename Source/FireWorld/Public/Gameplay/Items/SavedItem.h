#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "SavedItem.generated.h"

class UFWItem;

USTRUCT(Blueprintable)
struct FSavedItem
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	TSubclassOf<UFWItem> ItemClass = nullptr;

	UPROPERTY(SaveGame)
	TArray<uint8> SerializedData = TArray<uint8>();
};

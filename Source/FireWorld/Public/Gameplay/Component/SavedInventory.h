#pragma once

#include "CoreMinimal.h"
#include "SavedInventory.generated.h"

struct FSavedItem;

USTRUCT(Blueprintable)
struct FSavedInventory
{
	GENERATED_BODY()
	UPROPERTY(SaveGame)
	TArray<FSavedItem> Items = TArray<FSavedItem>();
};
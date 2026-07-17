#pragma once

#include "CoreMinimal.h"
#include "SavedInventory.generated.h"

struct FSavedItem;

USTRUCT(Blueprintable)
struct FSavedInventory
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<FSavedItem> Items = TArray<FSavedItem>();
};
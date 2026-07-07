#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Items/SavedItem.h"
#include "SavedInventory.generated.h"

USTRUCT(Blueprintable)
struct FSavedInventory
{
	GENERATED_BODY()
	TArray<FSavedItem> Items;
};
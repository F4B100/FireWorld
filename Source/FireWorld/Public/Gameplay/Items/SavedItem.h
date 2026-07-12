#pragma once

#include "CoreMinimal.h"
#include "UObject/SoftObjectPtr.h"
#include "SavedItem.generated.h"

class UFWItem;

USTRUCT(Blueprintable)
struct FSavedItem
{
	GENERATED_BODY()

	UPROPERTY()
	TSoftClassPtr<UFWItem> ItemClass;

	UPROPERTY()
	TArray<uint8> SerializedData;
};


#pragma once

#include "WeaponManagerSave.generated.h"

USTRUCT(BlueprintType)
struct FWeaponManagerSavedData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWeaponIndex = -1;
};
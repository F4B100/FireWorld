// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FWUIBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FWUI_API UFWUIBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "FWUI|Util")
	float StringToFloat(FString String);
};

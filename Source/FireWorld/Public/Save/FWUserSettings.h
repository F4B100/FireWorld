// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "FWUserSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Game|UserSettings")
	static UFWUserSettings* GetFWGameUserSettings();
};

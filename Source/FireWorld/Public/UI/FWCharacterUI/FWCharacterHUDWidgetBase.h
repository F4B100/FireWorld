// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWCharacterHUDWidgetBase.generated.h"

class AFWController;
class AFWCharacter;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWCharacterHUDWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWCharacter> FWCharacter = nullptr;

protected:
	virtual void NativePreConstruct() override;

};

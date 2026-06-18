// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWKeysMenu.generated.h"

class URemapableKey;
class UInputMappingContext;
class UEnhancedInputUserSettings;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWKeysMenu : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UPanelWidget> KeyPanel = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Input Settings")
	TObjectPtr<UEnhancedInputUserSettings> InputSettings = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TSubclassOf<URemapableKey> RemapableKeyWidgetClass = nullptr;

protected:
	virtual void NativeConstruct() override;
};

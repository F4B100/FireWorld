// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "RemapableKey.generated.h"

struct FPlayerKeyMapping;
class UTextBlock;
class UButton;
class UInputKeySelector;
/**
 * 
 */
UCLASS()
class FIREWORLD_API URemapableKey : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(Blueprintable)
	void UpdateKeyName();
	UFUNCTION(Blueprintable)
	void UpdateKey(FInputChord Key);

	UFUNCTION(Blueprintable)
	void KeySelectorChanged(FInputChord KeyChord);

	UFUNCTION(Blueprintable)
	void ClearClicked();
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> KeyBindName = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInputKeySelector> KeySelector = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ClearButton = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Input Settings")
	FPlayerKeyMapping KeyMapping = FPlayerKeyMapping();

	UPROPERTY(BlueprintReadOnly, Category = "Input Settings")
	TObjectPtr<UEnhancedInputUserSettings> PlayerSettings = nullptr;
};

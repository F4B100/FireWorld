// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWGraphicsSettings.generated.h"

class UComboBoxKey;
class UComboBoxString;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWGraphicsSettings : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UComboBoxKey> ScreenResDropdown = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TObjectPtr<UGameUserSettings> GameUserSettings = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TMap<FName, FIntPoint> Resolutions = TMap<FName, FIntPoint>();

	UFUNCTION(Blueprintable)
	void SelectionChanged(FName SelectedKey, ESelectInfo::Type SelectionType);

	/**
	 * Checks for available Screen Resolutions
	 * @param ScreenResOpts A reference to the data container with which to store the Screen Resolutions
	 */
	UFUNCTION(BlueprintCallable, Category = "Graphics Options")
	void UpdateScreenResOpts();

	/**
	 * Sets the given Screen Resolution
	 * @param InScreenRes The IntPoint with which to set the Screen Resolution
	 * @param bOverrideCommandLine Should the Game User Settings override conflicting command line settings
	 */
	UFUNCTION(BlueprintCallable, Category = "Graphics Options")
	void SetScreenRes(FIntPoint InScreenRes, bool bOverrideCommandLine);

	/**
	 * Stores the Game User Settings to Disk
	 * @param bOverrideCommandLine Should the Game User Settings override conflicting command line settings
	 */
	UFUNCTION(BlueprintCallable, Category = "Graphics Options")
	void ConfirmGameUserSettings(bool bOverrideCommandLine);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};

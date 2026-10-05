// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWGraphicsSettings.generated.h"

class UFWOptionSelector;
class UCheckBox;
class UFWEditableTextNumeric;
class UAnalogSlider;
class UTextBlock;
class UEditableText;
class UFWUserSettings;
class UComboBoxKey;
class UComboBoxString;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWGraphicsSettings : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UFWOptionSelector> FullScreenSelection = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UFWOptionSelector> ScreenResSelection = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCheckBox> VsyncCheckBox = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UAnalogSlider> FrameRateSlider = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UFWEditableTextNumeric> FPSEditableText = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TObjectPtr<UFWUserSettings> GameUserSettings = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TMap<FName, FIntPoint> Resolutions = TMap<FName, FIntPoint>();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Options")
	int FpsMin = 30;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Options")
	int FpsMax = 1000;

	UFUNCTION(Blueprintable)
	void SelectionChanged(FName SelectedKey, ESelectInfo::Type SelectionType);

	/**
	 * Checks for available Screen Resolutions
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

	UFUNCTION(Blueprintable)
	void UpdateFrameRateLimitValue(float NewValue);
	
	UFUNCTION()
	void HandleOnValueChangedFrameRateSlider(float Value);
	
	UFUNCTION()
	void HandleOnCheckStateChangedVsyncCheckBox(bool bIsChecked);
	
	UFUNCTION()
	void HandleOnValueCommitedFpsEditableText(float Value, ETextCommit::Type CommitMethod) const;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	virtual void BeginDestroy() override;
};

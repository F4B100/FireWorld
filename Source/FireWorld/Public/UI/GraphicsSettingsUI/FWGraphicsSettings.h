// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWGraphicsSettings.generated.h"

class UFWMenuObject;
class UButton;
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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> ApplySettingsButton = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> RestoreSettingsButton = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> FullScreenSelection = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> ScreenResSelection = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCheckBox> VsyncCheckBox = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UAnalogSlider> FrameRateSlider = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWEditableTextNumeric> FPSEditableText = nullptr;
	
	// Graphics settings
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> GlobalGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> ViewDistanceGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> ShadowGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> TextureGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> GIGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> ReflectionGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> AntiAliasingGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> VisualEffectGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> PostProcessingGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> FoliageGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> ShadingGraphicsSelection = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWOptionSelector> LandscapeGraphicsSelection = nullptr;
	
	int GetSelectedGraphicsOption(const UFWMenuObject* SelectedOptionSelector);
public:
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TObjectPtr<UFWUserSettings> GameUserSettings = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TMap<FName, FIntPoint> Resolutions = TMap<FName, FIntPoint>();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Options")
	int FpsMin = 30;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Options")
	int FpsMax = 1000;

	UFUNCTION(Blueprintable)
	void SelectionChangedGlobalGraphics(const UFWMenuObject* SelectedObject, const UFWOptionSelector* SelectedOptionSelector);
	UFUNCTION(Blueprintable)
	void SelectionChangedNonGlobal(const UFWMenuObject* SelectedObject, const UFWOptionSelector* SelectedOptionSelector);

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
	UFUNCTION(BlueprintCallable, Category = "Graphics Options")
	void SetWindowMode(int InWindowMode, bool bOverrideCommandLine);

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
	
	UFUNCTION()
	void HandleOnClickedApplySettingsButton();
	
	TArray<FString> GraphicsOptionMap = {
		TEXT("Low"),
		TEXT("Medium"),
		TEXT("High"),
		TEXT("Epic"),
		TEXT("Cinematic")
};
	TArray<TObjectPtr<UFWOptionSelector>> GraphicsOptionSelectors;

protected:
	void ApplyGraphicsQualitySetting(const UFWOptionSelector* Selector, int32 Quality);
	int32 GetGraphicsQualitySetting(const UFWOptionSelector* Selector) const;
	void UpdateGlobalGraphicsSelection();

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	virtual void BeginDestroy() override;
};

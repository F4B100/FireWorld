// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GraphicsSettingsUI/FWGraphicsSettings.h"

#include "AnalogSlider.h"
#include "Components/CheckBox.h"
#include "text/FWEditableTextNumeric.h"
#include "Components/ComboBoxKey.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "option/FWOptionSelector.h"
#include "Save/FWUserSettings.h"

void UFWGraphicsSettings::UpdateScreenResOpts()
{
	TArray<FIntPoint> SupportedScreenResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedScreenResolutions);

	Resolutions.Empty();

	for (FIntPoint SupportedScreenResolution : SupportedScreenResolutions)
	{
		FString KeyName = FString::Printf(TEXT("%i x %i"), SupportedScreenResolution.X, SupportedScreenResolution.Y);
		Resolutions.Emplace(FName(KeyName), SupportedScreenResolution);
	}
}

void UFWGraphicsSettings::SetScreenRes(FIntPoint InScreenRes, bool bOverrideCommandLine)
{
	if(GameUserSettings != nullptr)
	{
		GameUserSettings->SetScreenResolution(InScreenRes);
		GameUserSettings->ApplyResolutionSettings(bOverrideCommandLine);
	}
}

void UFWGraphicsSettings::ConfirmGameUserSettings(bool bOverrideCommandLine)
{
	if(GameUserSettings != nullptr)
	{
		GameUserSettings->ApplySettings(bOverrideCommandLine);
	}
}

void UFWGraphicsSettings::UpdateFrameRateLimitValue(float NewValue)
{
	if(GameUserSettings != nullptr)
	{
		GameUserSettings.Get()->SetFrameRateLimit(NewValue);
		ConfirmGameUserSettings(true);
	}
}

void UFWGraphicsSettings::HandleOnValueChangedFrameRateSlider(float Value)
{
	UpdateFrameRateLimitValue(Value);
	
	if (FPSEditableText)
	{
		FPSEditableText->SetTextValue(Value);
	}
}

void UFWGraphicsSettings::HandleOnCheckStateChangedVsyncCheckBox(bool bIsChecked)
{
	if (GameUserSettings)
	{
		GameUserSettings->SetVSyncEnabled(bIsChecked);
	}	
}

void UFWGraphicsSettings::HandleOnValueCommitedFpsEditableText(float Value,ETextCommit::Type CommitMethod) const
{
	if (FrameRateSlider)
	{
		FrameRateSlider->SetValue(Value);
	}
}


void UFWGraphicsSettings::SelectionChanged(FName SelectedKey, ESelectInfo::Type SelectionType)
{
	if (GameUserSettings == nullptr)
	{
		return;
	}

	if (Resolutions.Contains(SelectedKey))
	{
		FIntPoint SelectedResolution = Resolutions[SelectedKey];
		SetScreenRes(SelectedResolution, true);
	}
}

void UFWGraphicsSettings::NativePreConstruct()
{
	Super::NativePreConstruct();

	GameUserSettings = UFWUserSettings::GetFWGameUserSettings();

	GameUserSettings->LoadSettings();
	GameUserSettings->ApplySettings(true);

	GameUserSettings->ValidateSettings();
	
	FrameRateSlider->SetValue(GameUserSettings->GetFrameRateLimit());
	FPSEditableText->SetTextValue(GameUserSettings->GetFrameRateLimit());
}

void UFWGraphicsSettings::NativeConstruct()
{
	Super::NativeConstruct();
	if (ScreenResSelection)
	{
		
		UpdateScreenResOpts();

		for (const auto Opt : Resolutions)
		{
			ScreenResSelection.Get()->AddOption({.Name = Opt.Key.ToString(), .UserData = nullptr});
		}
		FIntPoint CurrentRes = GameUserSettings->GetScreenResolution();
		FName Current = FName(FString::Printf(TEXT("%i x %i"), CurrentRes.X, CurrentRes.Y));
		if (Resolutions.Contains(Current))
		{
			ScreenResSelection.Get()->SetSelected(Current.ToString());
		}
		else
		{
			Resolutions.Emplace(Current, GameUserSettings->GetScreenResolution());
			ScreenResSelection.Get()->AddOption({.Name = Current.ToString(), .UserData = nullptr});
			ScreenResSelection.Get()->SetSelected(Current.ToString());
		}
	}

	if (VsyncCheckBox)
	{
		
		VsyncCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UFWGraphicsSettings::HandleOnCheckStateChangedVsyncCheckBox);
	}

	if (FrameRateSlider)
	{
		FrameRateSlider->OnValueChanged.AddUniqueDynamic(this, &UFWGraphicsSettings::HandleOnValueChangedFrameRateSlider);
	}
	if (FPSEditableText)
	{
		FPSEditableText.Get()->OnValueCommitted.AddUniqueDynamic(this, &UFWGraphicsSettings::HandleOnValueCommitedFpsEditableText);
	}
	
}

void UFWGraphicsSettings::BeginDestroy()
{
	Super::BeginDestroy();
	if (GameUserSettings)
	{
		GameUserSettings->SaveSettings();
	}
}

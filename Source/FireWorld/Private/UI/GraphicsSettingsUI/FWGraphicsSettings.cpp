// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GraphicsSettingsUI/FWGraphicsSettings.h"

#include "AnalogSlider.h"
#include "../../../../../Plugins/FWUI/Source/FWUI/Public/text/FWNumericEditableText.h"
#include "Components/ComboBoxKey.h"
#include "Components/EditableText.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
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
	Resolutions.Emplace(FName(GameUserSettings->GetScreenResolution().ToString()), GameUserSettings->GetScreenResolution());
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

void UFWGraphicsSettings::HandleOnValueChangedFpsEditableText(float Value)
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
}

void UFWGraphicsSettings::NativeConstruct()
{
	Super::NativeConstruct();
	if (ScreenResDropdown)
	{
		ScreenResDropdown.Get()->ClearOptions();
		ScreenResDropdown.Get()->OnSelectionChanged.AddDynamic(this, &UFWGraphicsSettings::SelectionChanged);

		UpdateScreenResOpts();

		for (const auto Opt : Resolutions)
		{
			ScreenResDropdown.Get()->AddOption(Opt.Key);
		}
		FName Current = FName(GameUserSettings->GetScreenResolution().ToString());
		if (Resolutions.Contains(Current))
		{
			ScreenResDropdown.Get()->SetSelectedOption(Current);
		}
		else
		{
			Resolutions.Emplace(Current, GameUserSettings->GetScreenResolution());
			ScreenResDropdown.Get()->AddOption(Current);
			ScreenResDropdown.Get()->SetSelectedOption(Current);
		}
	}

	if (FrameRateSlider)
	{
		FrameRateSlider.Get()->SetValue(GameUserSettings->GetFrameRateLimit());
		FrameRateSlider->OnValueChanged.AddDynamic(this, &UFWGraphicsSettings::HandleOnValueChangedFrameRateSlider);
	}
	if (FPSEditableText)
	{
		FPSEditableText.Get()->OnValueChanged.AddDynamic(this, &UFWGraphicsSettings::HandleOnValueChangedFpsEditableText);
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

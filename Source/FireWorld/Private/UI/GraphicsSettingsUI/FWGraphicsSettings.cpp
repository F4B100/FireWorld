// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GraphicsSettingsUI/FWGraphicsSettings.h"

#include "AnalogSlider.h"
#include "Components/ComboBoxKey.h"
#include "Components/EditableText.h"
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
		GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(123153316, 1.0f, FColor::Yellow, FString::Printf(TEXT("Frame limit: %f\n"), NewValue));
	}
	GameUserSettings.Get()->SetFrameRateLimit(NewValue);
	GameUserSettings->ApplySettings(true);
	GameUserSettings->SaveSettings();
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
		FrameRateSlider->OnValueChanged.AddDynamic(this, &UFWGraphicsSettings::UpdateFrameRateLimitValue);
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GraphicsSettingsUI/FWGraphicsSettings.h"

#include "Components/ComboBoxKey.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

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

	GameUserSettings = UGameUserSettings::GetGameUserSettings();

	GameUserSettings->LoadSettings();
	GameUserSettings->ApplySettings(true);

	GameUserSettings->ValidateSettings();
}

void UFWGraphicsSettings::NativeConstruct()
{
	Super::NativeConstruct();
	if (ScreenResDropdown == nullptr)
	{
		return;
	}
	ScreenResDropdown.Get()->ClearOptions();
	ScreenResDropdown->OnSelectionChanged.AddDynamic(this, &UFWGraphicsSettings::SelectionChanged);

	UpdateScreenResOpts();

	for (auto Opt : Resolutions)
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

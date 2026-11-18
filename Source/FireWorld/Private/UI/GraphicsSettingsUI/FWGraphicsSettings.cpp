// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GraphicsSettingsUI/FWGraphicsSettings.h"

#include "AnalogSlider.h"
#include "PCGCommon.h"
#include "Components/CheckBox.h"
#include "text/FWEditableTextNumeric.h"
#include "Components/ComboBoxKey.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "option/FWOptionSelector.h"
#include "Save/FWUserSettings.h"

int UFWGraphicsSettings::GetSelectedGraphicsOption(const UFWMenuObject* SelectedOptionSelector)
{
	if (!SelectedOptionSelector)
	{
		return -1;
	}

	for (int i = 0; i < GraphicsOptionMap.Num(); i++)
	{
		if (SelectedOptionSelector->GetEntryData().Content.Compare(GraphicsOptionMap[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

void UFWGraphicsSettings::SelectionChangedGlobalGraphics(const UFWMenuObject* SelectedObject, const UFWOptionSelector* SelectedOptionSelector)
{
	const int32 Selected = GetSelectedGraphicsOption(SelectedObject);
	if (Selected >= 0)
	{
		for (const TObjectPtr<UFWOptionSelector>& Element : GraphicsOptionSelectors)
		{
			if (Element)
			{
				Element->SetSelected(GraphicsOptionMap[Selected], true);
			}
		}
	}
}

void UFWGraphicsSettings::SelectionChangedNonGlobal(const UFWMenuObject* SelectedObject, const UFWOptionSelector* SelectedOptionSelector)
{
	const int32 Selected = GetSelectedGraphicsOption(SelectedObject);
	if (Selected < 0 || !SelectedOptionSelector || !GameUserSettings)
	{
		return;
	}

	UpdateGlobalGraphicsSelection();
}

void UFWGraphicsSettings::ApplyGraphicsQualitySetting(const UFWOptionSelector* Selector, int32 Quality)
{
	if (!GameUserSettings || !Selector)
	{
		return;
	}

	if (Selector == ViewDistanceGraphicsSelection)
	{
		GameUserSettings->SetViewDistanceQuality(Quality);
	}
	else if (Selector == ShadowGraphicsSelection)
	{
		GameUserSettings->SetShadowQuality(Quality);
	}
	else if (Selector == TextureGraphicsSelection)
	{
		GameUserSettings->SetTextureQuality(Quality);
	}
	else if (Selector == GIGraphicsSelection)
	{
		GameUserSettings->SetGlobalIlluminationQuality(Quality);
	}
	else if (Selector == ReflectionGraphicsSelection)
	{
		GameUserSettings->SetReflectionQuality(Quality);
	}
	else if (Selector == AntiAliasingGraphicsSelection)
	{
		GameUserSettings->SetAntiAliasingQuality(Quality);
	}
	else if (Selector == VisualEffectGraphicsSelection)
	{
		GameUserSettings->SetVisualEffectQuality(Quality);
	}
	else if (Selector == PostProcessingGraphicsSelection)
	{
		GameUserSettings->SetPostProcessingQuality(Quality);
	}
	else if (Selector == FoliageGraphicsSelection)
	{
		GameUserSettings->SetFoliageQuality(Quality);
	}
	else if (Selector == ShadingGraphicsSelection)
	{
		GameUserSettings->SetShadingQuality(Quality);
	}
	else if (Selector == LandscapeGraphicsSelection)
	{
		GameUserSettings->SetLandscapeQuality(Quality);
	}
}

int32 UFWGraphicsSettings::GetGraphicsQualitySetting(const UFWOptionSelector* Selector) const
{
	if (!GameUserSettings || !Selector)
	{
		return -1;
	}

	if (Selector == ViewDistanceGraphicsSelection)
	{
		return GameUserSettings->GetViewDistanceQuality();
	}
	if (Selector == ShadowGraphicsSelection)
	{
		return GameUserSettings->GetShadowQuality();
	}
	if (Selector == TextureGraphicsSelection)
	{
		return GameUserSettings->GetTextureQuality();
	}
	if (Selector == GIGraphicsSelection)
	{
		return GameUserSettings->GetGlobalIlluminationQuality();
	}
	if (Selector == ReflectionGraphicsSelection)
	{
		return GameUserSettings->GetReflectionQuality();
	}
	if (Selector == AntiAliasingGraphicsSelection)
	{
		return GameUserSettings->GetAntiAliasingQuality();
	}
	if (Selector == VisualEffectGraphicsSelection)
	{
		return GameUserSettings->GetVisualEffectQuality();
	}
	if (Selector == PostProcessingGraphicsSelection)
	{
		return GameUserSettings->GetPostProcessingQuality();
	}
	if (Selector == FoliageGraphicsSelection)
	{
		return GameUserSettings->GetFoliageQuality();
	}
	if (Selector == ShadingGraphicsSelection)
	{
		return GameUserSettings->GetShadingQuality();
	}
	if (Selector == LandscapeGraphicsSelection)
	{
		return GameUserSettings->GetLandscapeQuality();
	}
	return -1;
}

void UFWGraphicsSettings::UpdateGlobalGraphicsSelection()
{
	if (!GlobalGraphicsSelection || GraphicsOptionSelectors.Num() == 0)
	{
		return;
	}

	const int32 FirstQuality = GetSelectedGraphicsOption(GraphicsOptionSelectors[0]->GetSelected());
	bool bAllMatch = FirstQuality >= 0;
	for (const TObjectPtr<UFWOptionSelector>& Selector : GraphicsOptionSelectors)
	{
		if (!Selector || GetSelectedGraphicsOption(Selector->GetSelected()) != FirstQuality)
		{
			bAllMatch = false;
			break;
		}
	}

	GlobalGraphicsSelection->SetSelected(
		bAllMatch && FirstQuality < GraphicsOptionMap.Num()
			? GraphicsOptionMap[FirstQuality]
			: TEXT("Custom"), true);
}

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

void UFWGraphicsSettings::SetWindowMode(int InWindowMode, bool bOverrideCommandLine)
{
	if (InWindowMode >= EWindowMode::NumWindowModes || InWindowMode < 0)
	{
		return;
	}
	if(GameUserSettings != nullptr)
	{
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

void UFWGraphicsSettings::HandleOnClickedApplySettingsButton()
{
	if (FullScreenSelection)
	{
		UFWMenuObject* FullscreenSelectionObject = FullScreenSelection->GetSelected();
		FString OptionContent = FullscreenSelectionObject->GetEntryData().Content;
		for (int i = 0; i < EWindowMode::NumWindowModes; ++i)
		{
			if (OptionContent.Equals( LexToString(EWindowMode::ConvertIntToWindowMode(i))))
			{
				SetWindowMode(i, true);
			}
		}
	}
	if (ScreenResSelection && ScreenResSelection->GetSelected())
	{
		UFWMenuObject* ResolutionObject = ScreenResSelection->GetSelected();
		if (Resolutions.Contains(*ResolutionObject->GetEntryData().Content))
		{
			FIntPoint SelectedResolution = Resolutions[*ResolutionObject->GetEntryData().Content];
			SetScreenRes(SelectedResolution, true);
		}
	}
	if (VsyncCheckBox)
	{
		GameUserSettings->SetVSyncEnabled(VsyncCheckBox->IsChecked());
	}
	if (GlobalGraphicsSelection)
	{
		const int32 GlobalQuality = GetSelectedGraphicsOption(GlobalGraphicsSelection->GetSelected());
		if (GlobalQuality >= 0)
		{
			GameUserSettings->SetOverallScalabilityLevel(GlobalQuality);
		}
	}
	for (const TObjectPtr<UFWOptionSelector>& Selector : GraphicsOptionSelectors)
	{
		const int32 Quality = Selector ? GetSelectedGraphicsOption(Selector->GetSelected()) : -1;
		if (Quality >= 0)
		{
			ApplyGraphicsQualitySetting(Selector, Quality);
		}
	}
	ConfirmGameUserSettings(true);
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
	
	GraphicsOptionSelectors = {
		ViewDistanceGraphicsSelection,
		ShadowGraphicsSelection,
		TextureGraphicsSelection,
		GIGraphicsSelection,
		ReflectionGraphicsSelection,
		AntiAliasingGraphicsSelection,
		VisualEffectGraphicsSelection,
		PostProcessingGraphicsSelection,
		FoliageGraphicsSelection,
		ShadingGraphicsSelection,
		LandscapeGraphicsSelection
	};
	
	if (FullScreenSelection)
	{
		for (int i = 0; i < EWindowMode::NumWindowModes; i++)
		{
			FullScreenSelection->AddOption({.Name = LexToString(EWindowMode::ConvertIntToWindowMode(i)), .UserData = nullptr});
		}
	}
	
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
			ScreenResSelection.Get()->SetSelected(Current.ToString(), false);
		}
		else
		{
			Resolutions.Emplace(Current, GameUserSettings->GetScreenResolution());
			ScreenResSelection.Get()->AddOption({.Name = Current.ToString(), .UserData = nullptr});
			ScreenResSelection.Get()->SetSelected(Current.ToString(), false);
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
	if (ApplySettingsButton)
	{
		ApplySettingsButton->OnClicked.AddUniqueDynamic(this, &UFWGraphicsSettings::HandleOnClickedApplySettingsButton);
	}

	if (GlobalGraphicsSelection)
	{
		for (const auto& Opt : GraphicsOptionMap)
		{
			GlobalGraphicsSelection->AddOption({.Name = Opt, .UserData = nullptr});
		}
		GlobalGraphicsSelection->AddOption({.Name = TEXT("Custom"), .UserData = nullptr});
		GlobalGraphicsSelection->OnSelectionChanged.AddUniqueDynamic(this, &UFWGraphicsSettings::SelectionChangedGlobalGraphics);
	}
	for (const auto& Selector : GraphicsOptionSelectors)
	{
		for (const auto& Opt : GraphicsOptionMap)
		{
			Selector->AddOption({.Name = Opt, .UserData = nullptr});
		}	
		Selector.Get()->OnSelectionChanged.__Internal_AddUniqueDynamic( this, &UFWGraphicsSettings::SelectionChangedNonGlobal, FName(UE::Core::Private::TrimmedMemberFunctionName<"&UFWGraphicsSettings::SelectionChangedNonGlobal">.Str) );
		const int32 Quality = FMath::Clamp(GetGraphicsQualitySetting(Selector), 0, GraphicsOptionMap.Num() - 1);
		Selector->SetSelected(GraphicsOptionMap[Quality], false);
	}
	UpdateGlobalGraphicsSelection();
}

void UFWGraphicsSettings::BeginDestroy()
{
	Super::BeginDestroy();
	if (GameUserSettings)
	{
		GameUserSettings->SaveSettings();
	}
}

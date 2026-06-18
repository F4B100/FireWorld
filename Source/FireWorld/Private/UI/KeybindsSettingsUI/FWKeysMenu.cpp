// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KeybindsSettingsUI/FWKeysMenu.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/PanelWidget.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "UI/KeybindsSettingsUI/RemapableKey.h"
#include "UserSettings/EnhancedInputUserSettings.h"

class UWidgetBlueprint;

void UFWKeysMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if (InputMappingContext == nullptr || KeyPanel == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputMappingContext or KeyPanel is null in UFWKeysMenu::NativeConstruct"));
		return;
	}

	KeyPanel->ClearChildren();

	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer());

	if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputSubsystem is null in UFWKeysMenu::NativeConstruct"));
		return;
	}

	const TObjectPtr<UEnhancedInputUserSettings> InputSettingsLocal = InputSubsystem->GetUserSettings();

	if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputSubsystem is null in UFWKeysMenu::NativeConstruct"));
		return;
	}

	int Tries;
	for(
		Tries = 0;
		!InputSettingsLocal.Get()->IsMappingContextRegistered(InputMappingContext) && Tries < 3;
		Tries++
	)
	{
		InputSettingsLocal.Get()->RegisterInputMappingContext(InputMappingContext);
	}
	InputSettingsLocal.Get()->LoadOrCreateSettings(GetOwningLocalPlayer());

	this->InputSettings = InputSettingsLocal;

	if (Tries > 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to register input mapping context after 3 tries."));
	}

	const TObjectPtr<UEnhancedPlayerMappableKeyProfile> ActiveKeyProfile = InputSettings.Get()->GetActiveKeyProfile();
	TMap<FName, FKeyMappingRow> KeyMappings = ActiveKeyProfile.Get()->GetPlayerMappingRows();

	for (auto KeyMapping : KeyMappings)
	{
		FKeyMappingRow MappingRow = KeyMapping.Value;
		bool IsKeyboardKeyOrControllerInput = true;
		for(auto Mapping : MappingRow.Mappings)
		{
			const FKey Key = Mapping.GetDefaultKey();
			if (Key.IsAxis2D() || Key.IsAxis1D() || Key.IsMouseButton())
			{
				IsKeyboardKeyOrControllerInput = false;
				break;
			}
		}
		if (!IsKeyboardKeyOrControllerInput)
		{
			continue;
		}

		TObjectPtr<URemapableKey> NewKeyWidget = CreateWidget<URemapableKey>(GetWorld(), RemapableKeyWidgetClass);

		NewKeyWidget.Get()->KeyMapping = MappingRow.Mappings.Get(FSetElementId::FromInteger(0));
		NewKeyWidget.Get()->PlayerSettings = InputSettings;

		if (NewKeyWidget)
		{
			KeyPanel->AddChild(NewKeyWidget);
		}
	}
}

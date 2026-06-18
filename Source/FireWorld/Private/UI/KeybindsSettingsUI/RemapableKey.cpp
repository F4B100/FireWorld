// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KeybindsSettingsUI/RemapableKey.h"

#include "Components/Button.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"

void URemapableKey::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateKeyName();
	UpdateKey(KeyMapping.GetCurrentKey());

	KeySelector.Get()->SetAllowModifierKeys(true);
	KeySelector.Get()->OnKeySelected.AddDynamic(this, &URemapableKey::KeySelectorChanged);

	ClearButton.Get()->OnClicked.AddDynamic(this, &URemapableKey::ClearClicked);
}

void URemapableKey::UpdateKeyName()
{
	const FText& DisplayName = KeyMapping.GetDisplayName();
	KeyBindName->SetText(DisplayName);
}

void URemapableKey::UpdateKey(FInputChord Key)
{
	KeySelector.Get()->SetSelectedKey(Key);
}

void URemapableKey::KeySelectorChanged(FInputChord KeyChord)
{
	if (PlayerSettings == nullptr)
	{
		return;
	}
	FMapPlayerKeyArgs Args = FMapPlayerKeyArgs();
	Args.MappingName = KeyMapping.GetMappingName();
	Args.Slot = EPlayerMappableKeySlot::First;
	Args.NewKey = KeyChord.Key;

	FGameplayTagContainer FailureReason;
	PlayerSettings.Get()->MapPlayerKey(Args, FailureReason);

	UpdateKey(KeyChord);
	PlayerSettings->SaveSettings();
}

void URemapableKey::ClearClicked()
{
	FMapPlayerKeyArgs Args = FMapPlayerKeyArgs();
	Args.Slot = EPlayerMappableKeySlot::First;
	Args.NewKey = KeyMapping.GetDefaultKey();

	FGameplayTagContainer FailureReason;
	PlayerSettings.Get()->MapPlayerKey(Args, FailureReason);

	PlayerSettings->SaveSettings();
	UpdateKeyName();
	UpdateKey(KeyMapping.GetDefaultKey());
}

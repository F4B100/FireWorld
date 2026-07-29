// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/FPPlayerUI.h"

#include "Character/FWCharacter.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Player/Inventory/PlayerInventoryView.h"

void UFPPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();

	FWCharacter = GetOwningPlayerPawn<AFWCharacter>();

	if (InputMappingComponent)
	{

	}
}

void UFPPlayerUI::ToggleInventory()
{
	if (InventorySwitcher && InventoryWidget && DefaultWidget)
	{
		if (InventorySwitcher.Get()->GetActiveWidget() == DefaultWidget)
		{
			InventoryFocusSwitched(true);
		}
		else
		{
			InventoryFocusSwitched(false);
		}
	}
}

bool UFPPlayerUI::IsInInventory()
{
	return InventorySwitcher.Get()->GetActiveWidget() == InventoryWidget;
}

void UFPPlayerUI::InventoryFocusSwitched_Implementation(bool InFocus)
{
}

void UFPPlayerUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (FWCharacter)
	{
		TObjectPtr<UPlayerStatsComponent> Stats = FWCharacter.Get()->GetPlayerStats();

	}
}

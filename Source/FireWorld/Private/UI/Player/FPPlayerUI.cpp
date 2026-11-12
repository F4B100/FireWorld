// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/FPPlayerUI.h"

#include "Character/FWCharacter.h"
#include "Gameplay/Component/WeaponManager.h"
#include "UI/Player/Inventory/InventoryItemView.h"
#include "UI/Player/Inventory/PlayerInventoryView.h"
#include "Gameplay/Items/FWItem.h"
#include "Gameplay/Items/Weapon.h"

void UFPPlayerUI::OnWeaponChangedHandler(UWeapon *Weapon) const
{
	if (CurrentWeapon)
	{
		CurrentWeapon.Get()->SetItem(Cast<UFWItem>(WeaponManager.Get()->GetCurrentWeapon()));
	}
}

void UFPPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();

	FWCharacter = GetOwningPlayerPawn<AFWCharacter>();

	if (FWCharacter)
	{
		WeaponManager = FWCharacter.Get()->GetWeaponManager();
	}
	if (CurrentWeapon)
	{
		WeaponManager->OnWeaponChanged.AddUniqueDynamic(this, &UFPPlayerUI::OnWeaponChangedHandler);
		CurrentWeapon.Get()->SetItem(Cast<UFWItem>(WeaponManager.Get()->GetCurrentWeapon()));
	}
	
	
}

void UFPPlayerUI::ToggleInventory()
{
	if (InventoryWidget && DefaultWidget)
	{
		if (!bIsInInventory)
		{
			bIsInInventory = true;
			DefaultWidget.Get()->SetIsEnabled(false);
			InventoryWidget.Get()->SetIsEnabled(true);
			PlayAnimationForward(ToggleInventoryAnimation);
		} else
		{
			bIsInInventory = false;
			DefaultWidget.Get()->SetIsEnabled(true);
			InventoryWidget.Get()->SetIsEnabled(false);
			PlayAnimationReverse(ToggleInventoryAnimation);
		}
	}
}

bool UFPPlayerUI::IsInInventory()
{
	return bIsInInventory;
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

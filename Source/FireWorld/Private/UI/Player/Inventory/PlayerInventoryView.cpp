// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/Inventory/PlayerInventoryView.h"

#include "Character/FWPlayerState.h"
#include "Gameplay/Component/ItemManagerComponent.h"
#include "UI/Player/Inventory/InventoryItemView.h"

void UPlayerInventoryView::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsDesignTime())
	{
		for (int i = 0; i < DesignTimeItems; ++i)
		{
			UWidget* TestChildren = CreateWidget<UInventoryItemView>(this, ItemViewClass);
			ItemContainer->AddChildToVerticalBox(TestChildren);
		}
	}
}

void UPlayerInventoryView::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerState = GetOwningPlayer()->GetPlayerState<AFWPlayerState>();

	if (PlayerState)
	{
		Inventory = PlayerState.Get()->GetItemManager();
	}
	if (!ItemViewClass)
	{
		return;
	}
	if (Inventory)
	{
		for (auto Item : Inventory.Get()->GetAllItems())
		{
			UInventoryItemView *NewWidget = CreateWidget<UInventoryItemView>(this, ItemViewClass);
			NewWidget->SetItem(Item);
			ItemContainer->AddChild(NewWidget);
		}
	}
}

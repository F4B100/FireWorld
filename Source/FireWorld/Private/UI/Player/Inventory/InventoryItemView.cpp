// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/Inventory/InventoryItemView.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Gameplay/Items/FWItem.h"

void UInventoryItemView::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryItemView::SetItem(const TObjectPtr<UFWItem> NewItem)
{
	if (!NewItem)
	{
		return;
	}
	Item = NewItem;
	if (ItemImage)
	{
		ItemImage.Get()->SetBrush(Item.Get()->GetItemBrush());
	}
	if (ItemName)
	{
		ItemName.Get()->SetText(FText::FromString(Item.Get()->GetName()));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Component/ItemManagerComponent.h"

#include "FWGameInstance.h"
#include "Character/FWCharacter.h"
#include "Character/FWPlayerState.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Gameplay/Items/FWItem.h"
#include "Save/FWSaveGame.h"
#include "Serialization/MemoryReader.h"

UItemManagerComponent::UItemManagerComponent()
{
}

void UItemManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AFWCharacter>(GetOwner());

	GameInstance = Cast<UFWGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Verbose, TEXT("Could Not Get GameInstance"))
	}
}

UFWItem *UItemManagerComponent::GetItem(int32 Index)
{
	if (Items.IsValidIndex(Index))
	{
		return Items[Index];
	}
	return nullptr;
}

TArray<UFWItem *> UItemManagerComponent::GetAllItems() const
{
	return Items;
}

void UItemManagerComponent::CollectItem(UFWItem *NewItem)
{
	if (NewItem)
	{
		OnItemAdded.Broadcast(NewItem, Items.Add(NewItem));
	}
}

void UItemManagerComponent::SaveInventory(FSavedInventory& Inventory) const
{
	Inventory.Items.Empty();
	for (const TObjectPtr<UFWItem>& I : Items)
	{
		FSavedItem& Item = Inventory.Items.Emplace_GetRef();
		I->CreateSavedItem(Item);
	}
}

void UItemManagerComponent::LoadInventory(FSavedInventory& Inventory)
{
	for (auto Item : Inventory.Items)
	{
		UClass *ItemClass = Item.ItemClass;
		UFWItem *NewItem = NewObject<UFWItem>(this, ItemClass);
		FMemoryReader Reader(Item.SerializedData);
		NewItem->Serialize(Reader);
		Items.Add(NewItem);
	}
}

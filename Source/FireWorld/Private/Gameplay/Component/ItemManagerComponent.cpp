// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Component/ItemManagerComponent.h"

#include "FWGameInstance.h"
#include "Character/FWCharacter.h"
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
		UE_LOG(LogTemp, Verbose, TEXT("g Could Not Get GameInstance"))
	}
	if (GameInstance && GameInstance.Get()->CurrentLoadedSave && GameInstance.Get()->CurrentLoadedSave)
	{
		LoadInventory(GameInstance.Get()->CurrentLoadedSave.Get()->SavedInventory);
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

TArray<UFWItem *> UItemManagerComponent::GetAllItems()
{
	return Items;
}

void UItemManagerComponent::CollectItem(UFWItem *NewItem)
{
	if (NewItem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(12576834, 10.0f, FColor::Magenta, NewItem->GetClass()->GetClassPathName().ToString());
		}
		OnItemAdded.Broadcast(NewItem, Items.Add(NewItem));
		if (GameInstance.Get()->CurrentLoadedSave)
		{
			SaveInventory(GameInstance.Get()->CurrentLoadedSave.Get()->SavedInventory);
		}
		GameInstance.Get()->SetShouldSaveGame(true);
	}
}

void UItemManagerComponent::SaveInventory(FSavedInventory& Inventory)
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
		UClass *ItemClass = Item.ItemClass.LoadSynchronous();
		UFWItem *NewItem = NewObject<UFWItem>(this, ItemClass);
		FMemoryReader Reader(Item.SerializedData);
		NewItem->Serialize(Reader);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/Component/ItemManagerComponent.h"

#include "FWGlobalGI.h"
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

	GameInstance = Cast<UFWGlobalGI>(GetWorld()->GetGameInstance());
	if (GameInstance && GameInstance.Get()->CurrentLoadedSave && GameInstance.Get()->CurrentLoadedSave)
	{
		LoadInventory(GameInstance.Get()->CurrentLoadedSave.Get()->SavedInventory);
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

void UItemManagerComponent::CollectItem(UFWItem *NewItem)
{
	if (NewItem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(12576834, 10.0f, FColor::Magenta, NewItem->GetName());
		}
		OnItemAdded.Broadcast(NewItem, Items.Add(NewItem));
	}
}

void UItemManagerComponent::SaveInventory(FSavedInventory& Inventory)
{
	for (const TObjectPtr<UFWItem>& I : Items)
	{
		FSavedItem& Item = Inventory.Items.Emplace_GetRef();
		I->CreateSavedItem(Item);
	}
}

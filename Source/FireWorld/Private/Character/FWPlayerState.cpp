// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FWPlayerState.h"

#include "FWGameInstance.h"
#include "Gameplay/Component/ItemManagerComponent.h"
#include "Save/FWSaveGame.h"

AFWPlayerState::AFWPlayerState()
{
	ItemManagerComponent = CreateDefaultSubobject<UItemManagerComponent>(TEXT("ItemManager"));
}

void AFWPlayerState::BeginPlay()
{
	Super::BeginPlay();

	FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());

	if (ItemManagerComponent && FWGameInstance)
	{
		ItemManagerComponent->LoadInventory(FWGameInstance.Get()->CurrentLoadedSave.Get()->SavedInventory);
	}
}

UItemManagerComponent* AFWPlayerState::GetItemManager()
{
	return ItemManagerComponent;
}

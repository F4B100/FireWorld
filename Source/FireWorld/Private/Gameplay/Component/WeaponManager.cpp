// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/WeaponManager.h"

#include "FWGlobalGI.h"
#include "Character/FWCharacter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Gameplay/Component/ItemManagerComponent.h"
#include "Gameplay/Items/Weapon.h"


UWeaponManager::UWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponManager::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SetWantsToFire(true);
	}
}

void UWeaponManager::EndFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SetWantsToFire(false);
	}
}

void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	ItemManager = Cast<AFWCharacter>(GetOwner())->GetItemManager();
	if (ItemManager)
	{
		ItemManager->OnItemRemoved.AddUObject(
			this,
			&UWeaponManager::HandleItemRemoved
		);

		ItemManager->OnItemAdded.AddUObject(
			this,
			&UWeaponManager::HandleItemAdded
		);

		ItemManager->OnItemMoved.AddUObject(
			this,
			&UWeaponManager::HandleItemChanged
		);
	}

	FWGameInstance = Cast<UFWGlobalGI>(GetWorld()->GetGameInstance());
	if (FWGameInstance)
	{
		if (FWGameInstance.Get()->CurrentLoadedSave)
		{
			UFWSaveGame *SaveGame = FWGameInstance.Get()->CurrentLoadedSave.Get();
		}
	}
}

void UWeaponManager::HandleItemRemoved(UFWItem* Item, int32 Index)
{
	if (CurrentWeapon == Item)
	{
		CurrentWeapon = nullptr;
	}
}

void UWeaponManager::HandleItemAdded(UFWItem* Item, int32 Index)
{
	if (!CurrentWeapon && Item->GetClass()->IsChildOf(UWeapon::StaticClass()))
	{
		CurrentWeapon = Cast<UWeapon>(Item);
	}
}

void UWeaponManager::HandleItemChanged(int32 Old, int32 New)
{

}

void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GEngine)
	{
		if (CurrentWeapon)
		{
			GEngine->AddOnScreenDebugMessage(2141278976, 10.0f, FColor::Black, CurrentWeapon->GetName());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(2141278976, 10.0f, FColor::Black, "No Weapon Equiped");
		}
	}
	if (CurrentWeapon)
	{
		CurrentWeapon->TickWeapon(DeltaTime);
	}
}


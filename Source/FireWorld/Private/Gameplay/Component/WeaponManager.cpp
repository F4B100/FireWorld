// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/WeaponManager.h"

#include "FWGameInstance.h"
#include "Character/FWCharacter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Gameplay/Component/ItemManagerComponent.h"
#include "Gameplay/Items/Weapon.h"


UWeaponManager::UWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	Owner = Cast<AFWCharacter>(GetOwner());
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

	FWGameInstance = Cast<UFWGameInstance>(GetWorld()->GetGameInstance());
}

void UWeaponManager::HandleItemRemoved(UFWItem* Item, int32 Index)
{
	if (CurrentWeapon == Item || CurrentWeaponIndex == Index)
	{
		ChangeEquippedWeapon(-1);
	}
}

void UWeaponManager::HandleItemAdded(UFWItem* Item, int32 Index)
{
	if (!CurrentWeapon && CurrentWeaponIndex < 0)
	{
		ChangeEquippedWeapon(Index);
	}
}

void UWeaponManager::HandleItemChanged(int32 Old, int32 New)
{
	if (CurrentWeaponIndex == Old)
	{
		ChangeEquippedWeapon(New);
	}
	if (CurrentWeaponIndex == New)
	{
		ChangeEquippedWeapon(Old);
	}
}

void UWeaponManager::ChangeEquippedWeapon(int32 Index, UWeapon *Weapon)
{
	if (Index < 0)
	{
		CurrentWeaponIndex = -1;
		CurrentWeapon = nullptr;
		return;
	}
	if (Weapon)
	{
		CurrentWeapon = Weapon;
		CurrentWeaponIndex = Index;
			CurrentWeapon.Get()->SwitchedInto(Owner);
		return;
	}
	TArray<UFWItem*> Items = ItemManager->GetAllItems();
	if (Items.IsEmpty())
	{
		return;
	}
	if (Items.IsValidIndex(Index))
	{
		UFWItem *Item = Items[Index];
		if (UWeapon *WeaponCast = Cast<UWeapon>(Item))
		{
			CurrentWeaponIndex = Index;
			CurrentWeapon = WeaponCast;
			CurrentWeapon.Get()->SwitchedInto(Owner);
		}
	}
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

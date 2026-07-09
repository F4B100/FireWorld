// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Interactible/WeaponPickUp.h"

#include "Character/FWCharacter.h"
#include "Engine/Engine.h"
#include "Gameplay/Component/ItemManagerComponent.h"
#include "Gameplay/Items/ProjectileWeapon.h"

AWeaponPickUp::AWeaponPickUp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponPickUp::InteractableInFocus(AFWCharacter* Interactee)
{
}

void AWeaponPickUp::InteractableOutOfFocus(AFWCharacter* Interactee)
{
}

void AWeaponPickUp::Interact(AFWCharacter* Interactee)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Test"));
	}
	if (Interactee)
	{
		TObjectPtr<UItemManagerComponent> ItemManager = Interactee->GetItemManager();

		if (ItemManager)
		{
			UProjectileWeapon *NewWeapon = NewObject<UProjectileWeapon>();
			ItemManager.Get()->CollectItem(NewWeapon);
		}
	}
}

FText AWeaponPickUp::GetInteractableActorName()
{
	return FText::FromString(TEXT("Weapon"));
}

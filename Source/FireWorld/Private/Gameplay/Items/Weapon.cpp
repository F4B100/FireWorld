// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Items/Weapon.h"

UWeapon::UWeapon()
{
}

void UWeapon::TickWeapon(float DeltaTime)
{
}

void UWeapon::SwitchedInto(TObjectPtr<AFWCharacter> Character)
{
	OwningCharacter = Character;
}

void UWeapon::SwitchedOut()
{
}

void UWeapon::SetWantsToFire(bool WantsToFire)
{
	bWantsToFire = WantsToFire;
}

bool UWeapon::GetWantsToFire()
{
	return bWantsToFire;
}

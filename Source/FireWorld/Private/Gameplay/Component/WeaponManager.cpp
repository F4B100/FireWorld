// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/WeaponManager.h"

#include "FWGlobalGI.h"
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

	FWGameInstance = Cast<UFWGlobalGI>(GetWorld()->GetGameInstance());
	if (FWGameInstance)
	{
		if (FWGameInstance.Get()->CurrentLoadedSave)
		{
			UFWSaveGame *SaveGame = FWGameInstance.Get()->CurrentLoadedSave.Get();
		}
	}
}


void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentWeapon)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(13141412, 10.0f, FColor::Black, CurrentWeapon->GetName());
		}
		CurrentWeapon->TickWeapon(DeltaTime);
	}
}


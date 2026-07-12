// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/Items/FWItem.h"
#include "WeaponManager.generated.h"


class AFWCharacter;
class UItemManagerComponent;
class UFWGameInstance;
class UWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

	TObjectPtr<AFWCharacter> Owner = nullptr;
	TObjectPtr<UItemManagerComponent> ItemManager = nullptr;

	int32 CurrentWeaponIndex = -1;
	TObjectPtr<UWeapon> CurrentWeapon = nullptr;

	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;

public:
	UWeaponManager();

	void StartFire();
	void EndFire();

protected:
	virtual void BeginPlay() override;
	void HandleItemRemoved(UFWItem* Item, int32 Index);
	void HandleItemAdded(UFWItem* Item, int32 Index);
	void HandleItemChanged(int32 Old, int32 New);

	void ChangeEquippedWeapon(int32 Index, UWeapon *Weapon = nullptr);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

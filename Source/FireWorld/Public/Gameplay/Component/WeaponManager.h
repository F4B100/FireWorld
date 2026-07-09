// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/Items/FWItem.h"
#include "WeaponManager.generated.h"


class UItemManagerComponent;
class UFWGlobalGI;
class UWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

	TObjectPtr<UItemManagerComponent> ItemManager;
	TObjectPtr<UWeapon> CurrentWeapon = nullptr;
	TObjectPtr<UFWGlobalGI> FWGameInstance = nullptr;

public:
	UWeaponManager();

	void StartFire();
	void EndFire();

protected:
	virtual void BeginPlay() override;
	void HandleItemRemoved(UFWItem* Item, int32 Index);
	void HandleItemAdded(UFWItem* Item, int32 Index);
	void HandleItemChanged(int32 Old, int32 New);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

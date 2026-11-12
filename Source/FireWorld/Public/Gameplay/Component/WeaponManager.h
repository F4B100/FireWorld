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

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<AFWCharacter> Owner = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UItemManagerComponent> ItemManager = nullptr;

	UPROPERTY(BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess))
	int32 CurrentWeaponIndex = -1;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UWeapon> CurrentWeapon = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, UWeapon *, NewWeapon);

public:
	UWeaponManager();
	
	FOnWeaponChanged OnWeaponChanged;
	
	UFUNCTION(BlueprintCallable)
	UWeapon *GetCurrentWeapon() {return CurrentWeapon;};

	void StartFire();
	void EndFire();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void LoadWeapons(FWeaponManagerSavedData &SaveData);
	UFUNCTION(BlueprintCallable)
	void SaveWeapons(FWeaponManagerSavedData& SaveData);
	
	virtual void Serialize(FArchive& Ar) override;
protected:
	void HandleItemRemoved(UFWItem* Item, int32 Index);
	void HandleItemAdded(UFWItem* Item, int32 Index);
	void HandleItemChanged(int32 Old, int32 New);

	void ChangeEquippedWeapon(int32 Index, UWeapon *Weapon = nullptr);
	
	UFUNCTION()
	void HandleInventoryLoaded();
};

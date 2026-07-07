// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"


class UFWGlobalGI;
class UWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

	UWeapon *CurrentWeapon = nullptr;
	TObjectPtr<UFWGlobalGI> FWGameInstance = nullptr;

public:
	UWeaponManager();

	void StartFire();
	void EndFire();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

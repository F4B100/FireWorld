// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWItem.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"

class AFWCharacter;

UCLASS(ClassGroup=(Custom), Blueprintable)
class FIREWORLD_API UWeapon : public UFWItem
{
	GENERATED_BODY()

	bool bWantsToFire = false;
public:
	UWeapon();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWCharacter> OwningCharacter = nullptr;

	virtual void TickWeapon(float DeltaTime);

	virtual void SwitchedInto(TObjectPtr<AFWCharacter> Character);
	virtual void SwitchedOut();

	UFUNCTION(Blueprintable)
	void SetWantsToFire(bool WantsToFire);
	UFUNCTION(Blueprintable)
	bool GetWantsToFire();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractibleActor.h"
#include "GameFramework/Actor.h"
#include "WeaponPickUp.generated.h"

class UWeapon;
class AFWCharacter;
class ACharacter;

UCLASS()
class FIREWORLD_API AWeaponPickUp : public AActor, public IInteractableActor
{
	GENERATED_BODY()

public:
	AWeaponPickUp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWeapon> Weapon;

	UFUNCTION(BlueprintCallable)
	virtual void InteractableInFocus(AFWCharacter* Interactee) override;
	UFUNCTION(BlueprintCallable)
	virtual void InteractableOutOfFocus(AFWCharacter* Interactee) override;
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AFWCharacter* Interactee) override;
	UFUNCTION(BlueprintCallable)
	virtual FText GetInteractableActorName() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ProjectileWeapon.generated.h"


class AFWProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UProjectileWeapon : public UWeapon
{
	GENERATED_BODY()
	float CurrentFiringTime = 0.0f;
	float FiringCooldown = 0.5f;

public:
	UProjectileWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AFWProjectile> ProjectileClass;

	virtual void TickWeapon(float DeltaTime) override;

	virtual void SwitchedInto(TObjectPtr<AFWCharacter> Character) override;
	virtual void SwitchedOut() override;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void ServerPerformFire();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum EWeaponFiringType
{
	FIRE_NONE UMETA(Hidden),
	FIRE_SINGLE UMETA(DisplayName = "Single fire"),
	FIRE_MAX UMETA(DisplayName = "Max")
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UWeapon : public UActorComponent
{
	GENERATED_BODY()
	float TimeSinceLastFire = 0.0f;

public:
	UWeapon();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bWantsToFire = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireCooldown = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EWeaponFiringType> FiringType = FIRE_SINGLE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFWProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerPerformFire();

protected:
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};

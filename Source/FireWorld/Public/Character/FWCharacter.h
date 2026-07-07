// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FWCharacter.generated.h"

class UInteractionManager;
class AFWController;
class UWeaponManager;
class UKeyInventoryComponent;
class UItemManagerComponent;
class UStablePositionUpdater;
class UPlayerStatsComponent;
class UWeapon;
class UFWGlobalGI;
class UFWCharacterMovementComponent;
class UInputAction;

UCLASS(Blueprintable)
class FIREWORLD_API AFWCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	explicit AFWCharacter(FObjectInitializer const &);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Bool)
	bool bShouldReadSaveData = false;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFWGlobalGI> FWGameInstance = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWController> FWController = nullptr;


	//=========================Components=========================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	TObjectPtr<UFWCharacterMovementComponent> FWMovementComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPlayerStatsComponent> PlayerStats = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStablePositionUpdater> StablePositionUpdater = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UItemManagerComponent> ItemInventory = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UKeyInventoryComponent> KeyInventory = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWeaponManager> WeaponManager = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInteractionManager> InteractionManager = nullptr;
	//============================================================
	FString Level = FString("");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float KnockbackMultiplier = 1;

	void AddLookInput(const FVector2D& Look);
	void AddMovementInput(const FVector2D& Move);
	
	void SprintPressed() const;
	void SprintReleased() const;
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Fire();
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void StopFire();

	TObjectPtr<UFWCharacterMovementComponent> GetFWMovementComponent() {return FWMovementComponent;}
	
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce = false) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginDestroy() override;

	FCollisionQueryParams GetIgnoreCharacterParams();
	UFUNCTION(BlueprintCallable)
	UInteractionManager *GetInteractionManager() {return InteractionManager;}

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void LaunchCharacterServer(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void Interact();
};

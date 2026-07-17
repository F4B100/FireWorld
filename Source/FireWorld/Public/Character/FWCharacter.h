// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FWCharacter.generated.h"

class UInteractionManagerComponent;
class AFWController;
class UWeaponManager;
class UKeyInventoryComponent;
class UItemManagerComponent;
class UStablePositionUpdater;
class UPlayerStatsComponent;
class UWeapon;
class UFWGameInstance;
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
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWController> FWController = nullptr;


	//=========================Components=========================
	UPROPERTY(EditDefaultsOnly, Category=Movement)
	TObjectPtr<UFWCharacterMovementComponent> FWMovementComponent = nullptr;
	UFUNCTION(BlueprintCallable)
	UFWCharacterMovementComponent *GetFWMovementComponent() {return FWMovementComponent;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPlayerStatsComponent> PlayerStats = nullptr;
	UFUNCTION(BlueprintCallable)
	UPlayerStatsComponent *GetPlayerStats() {return PlayerStats;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStablePositionUpdater> StablePositionUpdater = nullptr;
	UFUNCTION(BlueprintCallable)
	UStablePositionUpdater *GetStablePositionUpdater() {return StablePositionUpdater;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UItemManagerComponent> ItemManager = nullptr;
	UFUNCTION(BlueprintCallable)
	UItemManagerComponent *GetItemManager() {return ItemManager;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UKeyInventoryComponent> KeyManager = nullptr;
	UFUNCTION(BlueprintCallable)
	UKeyInventoryComponent *GetKeyInventory() {return KeyManager;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWeaponManager> WeaponManager = nullptr;
	UFUNCTION(BlueprintCallable)
	UWeaponManager *GetWeaponManager() {return WeaponManager;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInteractionManagerComponent> InteractionManager = nullptr;
	UFUNCTION(BlueprintCallable)
	UInteractionManagerComponent *GetInteractionManager() {return InteractionManager;}
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

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce = false) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginDestroy() override;

	FCollisionQueryParams GetIgnoreCharacterParams();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void LaunchCharacterServer(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void Interact();
};

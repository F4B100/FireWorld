// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FWCharacterFP.generated.h"

class UPlayerStatsComponent;
class UWeapon;
class UFWGlobalGI;
class UFWCharacterMovementComponent;
class UInputAction;

UCLASS(Blueprintable)
class FIREWORLD_API AFWCharacterFP : public ACharacter
{
	GENERATED_BODY()
public:
	explicit AFWCharacterFP(FObjectInitializer const &);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	TObjectPtr<UFWCharacterMovementComponent> FWMovementComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Bool)
	bool bShouldReadSaveData = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UFWGlobalGI> GameInstance = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPlayerStatsComponent> PlayerStats = nullptr;

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

	virtual void Tick(float DeltaTime) override;
	
	TObjectPtr<UFWCharacterMovementComponent> GetFWMovementComponent() {return FWMovementComponent;}
	
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce = false) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginDestroy() override;

	FCollisionQueryParams GetIgnoreCharacterParams();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void LaunchCharacterServer(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
};

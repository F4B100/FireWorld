// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UPlayerStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerStatsComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = Options)
	float Health = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float MaxHealth = Health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float HealthRegenRate = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = Options)
	float Stamina = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float MaxStamina = Stamina;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float StaminaRegenRate = 1;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	float GetHealth() const {return Health;}
	UFUNCTION(BlueprintCallable, Category = Health)
	float GetMaxHealth() const {return MaxHealth;}
	UFUNCTION(BlueprintCallable, Category = Stamina)
	float GetStamina() const {return Stamina;}
	UFUNCTION(BlueprintCallable, Category = Stamina)
	float GetMaxStamina() const {return MaxStamina;}


	UFUNCTION(BlueprintCallable, Category = Health)
	void DoDamage(float Damage);
	UFUNCTION(BlueprintCallable, Category = Health)
	void RestoreHealth(float HealthToRestore);
};

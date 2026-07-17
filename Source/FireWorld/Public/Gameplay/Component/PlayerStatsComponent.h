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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float Health = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float MaxHealth = Health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float HealthRegenRate = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float Stamina = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float MaxStamina = Stamina;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	float StaminaRegenRate = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	void DoDamage(float Damage);
	UFUNCTION(BlueprintCallable, Category = Health)
	void RestoreHealth(float HealthToRestore);
};

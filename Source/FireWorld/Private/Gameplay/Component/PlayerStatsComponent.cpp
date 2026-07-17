// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/PlayerStatsComponent.h"


UPlayerStatsComponent::UPlayerStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPlayerStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Health = FMath::Min(Health + HealthRegenRate * DeltaTime, MaxHealth);
	Stamina = FMath::Min(Stamina + StaminaRegenRate * DeltaTime, MaxStamina);
}

void UPlayerStatsComponent::DoDamage(float Damage)
{
	Health = FMath::Max(Health - Damage, 0.0f);
}

void UPlayerStatsComponent::RestoreHealth(float HealthToRestore)
{
	Health = FMath::Min(Health + HealthToRestore, MaxHealth);
}


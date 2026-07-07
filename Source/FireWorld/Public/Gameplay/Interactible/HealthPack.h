// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractibleActor.h"
#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

UCLASS()
class FIREWORLD_API AHealthPack : public AActor, public IInteractibleActor
{
	GENERATED_BODY()

public:
	AHealthPack();

	FText Name =  FText::FromString(TEXT("Health Pack"));

	UFUNCTION(BlueprintCallable)
	virtual void InteractibleInFocus(ACharacter* Interactee) override;
	UFUNCTION(BlueprintCallable)
	virtual void InteractibleOutOfFocus(ACharacter* Interactee) override;
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AFWCharacter* Interactee) override;
	UFUNCTION(BlueprintCallable)
	virtual FText GetInteractibleActorName() override;
};

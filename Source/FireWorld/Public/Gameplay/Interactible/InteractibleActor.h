// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractibleActor.generated.h"

class AFWCharacter;
// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractibleActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIREWORLD_API IInteractibleActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void InteractibleInFocus(ACharacter* Interactee);
	UFUNCTION()
	virtual void InteractibleOutOfFocus(ACharacter* Interactee);
	UFUNCTION()
	virtual void Interact(AFWCharacter* Interactee);
	UFUNCTION()
	virtual FText GetInteractibleActorName();
};

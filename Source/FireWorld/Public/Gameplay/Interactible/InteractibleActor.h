// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractibleActor.generated.h"

class ACharacter;
class AFWCharacter;
// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractableActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIREWORLD_API IInteractableActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void InteractableInFocus(AFWCharacter* Interactee);
	UFUNCTION()
	virtual void InteractableOutOfFocus(AFWCharacter* Interactee);
	UFUNCTION()
	virtual void Interact(AFWCharacter* Interactee);
	UFUNCTION()
	virtual FText GetInteractableActorName();
};

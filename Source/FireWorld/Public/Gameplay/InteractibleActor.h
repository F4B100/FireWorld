// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractibleActor.generated.h"

// This class does not need to be modified.
UINTERFACE()
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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InteractibleInFocus(ACharacter* Interactee);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InteractibleOutOfFocus(ACharacter* Interactee);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Interact(ACharacter* Interactee);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FText GetInteractibleActorName();
};

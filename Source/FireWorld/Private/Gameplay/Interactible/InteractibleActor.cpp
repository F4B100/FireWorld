// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Interactible/InteractibleActor.h"


// Add default functionality here for any IInteractibleActor functions that are not pure virtual.
void IInteractibleActor::InteractibleInFocus(ACharacter* Interactee)
{
}

void IInteractibleActor::InteractibleOutOfFocus(ACharacter* Interactee)
{
}

void IInteractibleActor::Interact(AFWCharacter* Interactee)
{
}

FText IInteractibleActor::GetInteractibleActorName()
{
	return FText::FromString(TEXT("Default interactible\n"));
}

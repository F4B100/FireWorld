// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Interactible/InteractibleActor.h"


// Add default functionality here for any IInteractableActor functions that are not pure virtual.
void IInteractableActor::InteractableInFocus(AFWCharacter* Interactee)
{
}

void IInteractableActor::InteractableOutOfFocus(AFWCharacter* Interactee)
{
}

void IInteractableActor::Interact(AFWCharacter* Interactee)
{
}

FText IInteractableActor::GetInteractableActorName()
{
	return FText::FromString(TEXT("Default interactible\n"));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Interactible/HealthPack.h"

#include "Character/FWCharacter.h"


AHealthPack::AHealthPack()
{
}

void AHealthPack::InteractibleInFocus(ACharacter* Interactee)
{
}

void AHealthPack::InteractibleOutOfFocus(ACharacter* Interactee)
{
}

void AHealthPack::Interact(AFWCharacter* Interactee)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, Interactee->GetName());
	}
}

FText AHealthPack::GetInteractibleActorName()
{
	return Name;
}


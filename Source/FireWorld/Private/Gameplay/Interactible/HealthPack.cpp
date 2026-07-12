// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Interactible/HealthPack.h"

#include "Character/FWCharacter.h"
#include "Engine/Engine.h"
#include "Gameplay/Component/PlayerStatsComponent.h"


AHealthPack::AHealthPack()
{
}

void AHealthPack::InteractableInFocus(AFWCharacter* Interactee)
{
}

void AHealthPack::InteractableOutOfFocus(AFWCharacter* Interactee)
{
}

void AHealthPack::Interact(AFWCharacter* Interactee)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, Interactee->GetName());
	}
	Interactee->GetPlayerStats()->RestoreHealth(10.0f);
}

FText AHealthPack::GetInteractableActorName()
{
	return Name;
}


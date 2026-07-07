// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FWCharacterUI/FWCharacterHUDWidgetBase.h"

#include "Character/FWCharacter.h"

void UFWCharacterHUDWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	APawn* Pawn = GetOwningPlayerPawn();

	UE_LOG(LogTemp, Warning, TEXT("Pawn: %s"),
		Pawn ? *Pawn->GetName() : TEXT("nullptr"));

	FWCharacter = Cast<AFWCharacter>(Pawn);

	UE_LOG(LogTemp, Warning, TEXT("Character: %s"),
		FWCharacter ? *FWCharacter->GetName() : TEXT("nullptr"));
}

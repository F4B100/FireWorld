// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaveSelect/FWSaveCreator.h"

#include "FWGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UFWSaveCreator::OnStartGameClicked()
{
	if (SaveNameTextBox && !SaveNameTextBox.Get()->GetText().IsEmpty())
	{
		FWGameInstance.Get()->CreateSaveGame(SaveNameTextBox.Get()->GetText().ToString());
	}
}


void UFWSaveCreator::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (StartGameButton)
	{
		StartGameButton.Get()->OnClicked.AddDynamic(this, &UFWSaveCreator::OnStartGameClicked);
	}
	FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());
}

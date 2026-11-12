// Fill out your copyright notice in the Description page of Project Settings.


#include "FWSwitchableMenuEntry.h"

#include "Components/Button.h"

void UFWSwitchableMenuEntry::OnExitButtonClicked()
{
	if (OnExitClicked.IsBound())
	{
		OnExitClicked.Broadcast();
	}
}

void UFWSwitchableMenuEntry::NativeConstruct()
{
	Super::NativeConstruct();
	if (ExitButton)
	{
		ExitButton.Get()->OnClicked.AddDynamic(this, &UFWSwitchableMenuEntry::OnExitButtonClicked);
	}
}

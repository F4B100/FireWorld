// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FWCharacterHUD.h"

#include "Blueprint/UserWidget.h"
#include "Character/FWCharacter.h"
#include "Controller/FWController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Player/FWPlayerInteractionWidget.h"

void AFWCharacterHUD::BeginPlay()
{
	Super::BeginPlay();
	if (!UKismetSystemLibrary::IsServer(GetWorld()))
	{
		return;
	}
	FWController = Cast<AFWController>(GetOwningPlayerController());
	if (FWController)
	{
		FWCharacter = Cast<AFWCharacter>(FWController->GetCharacter());
	}
	SwitchDisplayedWidget(MainWidgetClass, TEXT("Character Main Widget"));
}

void AFWCharacterHUD::SwitchDisplayedWidget(TSubclassOf<UFPPlayerUI> WidgetClass, FName WidgetName)
{
	if (FWController)
	{
		if (MainWidget)
		{
			MainWidget->RemoveFromParent();
		}
		MainWidget = CreateWidget<UFPPlayerUI>(FWController, WidgetClass, WidgetName);
		MainWidget->AddToViewport();
	}
}

void AFWCharacterHUD::ToggleInventory()
{
	MainWidget.Get()->ToggleInventory();
}

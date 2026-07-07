// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FWCharacterHUD.h"

#include "Blueprint/UserWidget.h"
#include "Character/FWCharacter.h"
#include "Controller/FWController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/FWCharacterUI/FWPlayerInteractionWidget.h"

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

void AFWCharacterHUD::SwitchDisplayedWidget(TSubclassOf<UFWCharacterWidget> WidgetClass, FName WidgetName)
{
	if (FWController)
	{
		if (MainWidget)
		{
			MainWidget->RemoveFromParent();
		}
		MainWidget = CreateWidget<UFWCharacterWidget>(FWController, WidgetClass, WidgetName);
		MainWidget->AddToViewport();
	}
}

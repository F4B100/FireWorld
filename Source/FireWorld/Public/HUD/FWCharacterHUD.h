// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Player/FPPlayerUI.h"
#include "FWCharacterHUD.generated.h"

class UInteractableActor;
class AFWController;
class UFPPlayerUI;
class UCommonUserWidget;
/**
 *
 */
UCLASS()
class FIREWORLD_API AFWCharacterHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFPPlayerUI> MainWidget = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWController> FWController = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWCharacter> FWCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UFPPlayerUI> MainWidgetClass = UFPPlayerUI::StaticClass();

protected:
	virtual void BeginPlay() override;
	void SwitchDisplayedWidget(TSubclassOf<UFPPlayerUI> WidgetClass, FName WidgetName);
	void ToggleInventory();
};

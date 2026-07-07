// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/FWCharacterUI/FWCharacterWidget.h"
#include "FWCharacterHUD.generated.h"

class UInteractibleActor;
class AFWController;
class UFWCharacterWidget;
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
	TObjectPtr<UFWCharacterWidget> MainWidget = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWController> FWController = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFWCharacter> FWCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UFWCharacterWidget> MainWidgetClass = UFWCharacterWidget::StaticClass();

protected:
	virtual void BeginPlay() override;
	void SwitchDisplayedWidget(TSubclassOf<UFWCharacterWidget> WidgetClass, FName WidgetName);
};

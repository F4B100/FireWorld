// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWSwitchableMenuEntry.h"
#include "FWSaveCreator.generated.h"

class UFWGameInstance;
class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWSaveCreator : public UFWSwitchableMenuEntry
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> StartGameButton = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UEditableTextBox> SaveNameTextBox = nullptr;
	
	UFUNCTION()
	void OnStartGameClicked();
protected:
	virtual void NativeConstruct() override;
};
	
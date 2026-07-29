// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SaveSelect.generated.h"

class UScrollBox;
class USaveInfo;
class UEditableTextBox;
class UVerticalBox;
class UFWGameInstance;
class UButton;
/**
 * 
 */
UCLASS()
class FIREWORLD_API USaveSelect : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreateSaveButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SavesContainer = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> SaveName = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveInfo> SaveInfoClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LevelToLoad = nullptr;

	void NativeConstruct() override;
	UFUNCTION()
	void OnCreateSaveClicked();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWSwitchableMenuEntry.h"
#include "Save/FWSaveGame.h"
#include "FWSaveSelect.generated.h"

class UScrollBox;
class UFWSaveInfo;
class UEditableTextBox;
class UVerticalBox;
class UFWGameInstance;
class UButton;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWSaveSelect : public UFWSwitchableMenuEntry
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SavesContainer = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFWSaveInfo> SaveInfoClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LevelToLoad = nullptr;

	UFUNCTION()
	void OnSaveGameAdded(const FString& Name, UFWSaveGame *SaveObject);

protected:
	virtual void NativeConstruct() override;
};

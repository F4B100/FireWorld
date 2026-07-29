// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SaveInfo.generated.h"

class UTextBlock;
class UFWSaveGame;
class UFWGameInstance;
class UButton;
/**
 * 
 */
UCLASS()
class FIREWORLD_API USaveInfo : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFWGameInstance> FWGameInstance = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFWSaveGame> FWSaveGame = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FString FWSaveName = FString();

	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSoftObjectPtr<UWorld> LevelToLoad;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MainButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DeleteSaveButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SaveName;

	void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void LoadSaveInfo(FString SaveToLoad);
	UFUNCTION(BlueprintCallable)
	void MainButtonClicked();
	UFUNCTION(BlueprintCallable)
	void DeleteSaveButtonClicked();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FWGameInstance.generated.h"

class UFWSaveNames;
class UFWSaveGame;
class UFWUserSettings;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWGameInstance : public UGameInstance
{
	GENERATED_BODY()

	FString SaveNamesName = FString("SaveNames");
public:
	// Variables
	UPROPERTY(BlueprintReadOnly, Category=Save)
	TObjectPtr<UFWSaveNames> SaveNames = nullptr;

	UPROPERTY(BlueprintReadWrite, Category=Save)
	TObjectPtr<UFWSaveGame> CurrentLoadedSave = nullptr;
	UPROPERTY(BlueprintReadOnly, Category=Save)
	FString LoadedSaveName = FString();

	UPROPERTY(BlueprintReadOnly, Category=Save)
	bool bShouldSaveGame = false;
	UFUNCTION(BlueprintCallable)
	bool GetShouldSaveGame(){return bShouldSaveGame;}
	UFUNCTION(BlueprintCallable)
	void SetShouldSaveGame(const bool New){bShouldSaveGame = New;}

	UPROPERTY(BlueprintReadOnly, Category=Save)
	TObjectPtr<UFWUserSettings> UserSettings = nullptr;

	// Functions
	UFWGameInstance();

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void SaveSaveNames();
	UFUNCTION(BlueprintCallable)
	bool CreateSaveGame(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	bool DeleteSaveGame(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	bool ChangeLoadedSaveGame(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	bool HasLoadedSaveGame() const;
	UFUNCTION(BlueprintCallable)
	bool DoesSaveExist(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	TArray<FString> SaveNamesArray();

	UFUNCTION(BlueprintCallable)
	UFWSaveGame *GetSaveGame(const FString SaveName);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FWGlobalGI.generated.h"

class UFWSaveNames;
class UFWSaveGame;
class UFWUserSettings;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWGlobalGI : public UGameInstance
{
	FString SaveNamesName = FString("SaveNames");
public:
	UPROPERTY(BlueprintReadOnly, Category=Save)
	TObjectPtr<UFWSaveNames> SaveNames = nullptr;
	UPROPERTY(BlueprintReadWrite, Category=Save)
	TObjectPtr<UFWSaveGame> CurrentLoadedSave = nullptr;
	UPROPERTY(BlueprintReadOnly, Category=Save)
	FString LoadedSaveName = FString("");
	UPROPERTY(BlueprintReadOnly, Category=Save)
	TObjectPtr<UFWUserSettings> UserSettings = nullptr;
	
	UFWGlobalGI();

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	bool CreateSaveGame(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	bool ChangeLoadedSaveGame(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	bool HasLoadedSaveGame() const;
	UFUNCTION(BlueprintCallable)
	bool DoesSaveExist(const FString SaveName);
	UFUNCTION(BlueprintCallable)
	TArray<FString> SaveNamesArray();
private:
	GENERATED_BODY()
};

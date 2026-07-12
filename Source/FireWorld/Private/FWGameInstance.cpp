// Fill out your copyright notice in the Description page of Project Settings.


#include "FWGameInstance.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Save/FWSaveGame.h"
#include "Save/FWSaveNames.h"
#include "Save/FWUserSettings.h"

UFWGameInstance::UFWGameInstance()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveNamesName, 0))
	{
		SaveNames = Cast<UFWSaveNames>(UGameplayStatics::LoadGameFromSlot(SaveNamesName, 0));
		if (SaveNames == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load save object in FW Game Instance."));
		}
	} else
	{
		SaveNames = Cast<UFWSaveNames>(UGameplayStatics::CreateSaveGameObject(UFWSaveNames::StaticClass()));
		if (SaveNames == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create save object in FW Game Instance."));
			return;
		}
		UGameplayStatics::SaveGameToSlot(SaveNames, SaveNamesName, 0);
	}
}

void UFWGameInstance::SaveGame()
{
	if (!CurrentLoadedSave)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Save data not available at save time."));
		UE_LOG(LogTemp, Error, TEXT("Save data not available at save time."));
		if (!CreateSaveGame(LoadedSaveName))
		{
			return;
		}
	}
	UGameplayStatics::SaveGameToSlot(CurrentLoadedSave, LoadedSaveName, 0);
	bShouldSaveGame = false;
}

bool UFWGameInstance::CreateSaveGame(const FString SaveName)
{
	if (SaveNames.Get()->SaveNames.Contains(SaveName))
		return false;
	SaveNames.Get()->SaveNames.Emplace(SaveName);
	UGameplayStatics::SaveGameToSlot(SaveNames, SaveNamesName, 0);
	CurrentLoadedSave = Cast<UFWSaveGame>(UGameplayStatics::CreateSaveGameObject(UFWSaveGame::StaticClass()));

	if (CurrentLoadedSave == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create save object in FW Game Instance."));
		return false;
	}
	return true;
}

bool UFWGameInstance::ChangeLoadedSaveGame(const FString SaveName)
{
	if (!SaveNames.Get()->SaveNames.Contains(SaveName))
		return false;
	if (CurrentLoadedSave != nullptr)
		UGameplayStatics::SaveGameToSlot(CurrentLoadedSave, LoadedSaveName, 0);
	LoadedSaveName = SaveName;
	if (UGameplayStatics::DoesSaveGameExist(SaveName, 0))
	{
		CurrentLoadedSave = Cast<UFWSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadedSaveName, 0));
	} else
	{
		CurrentLoadedSave = Cast<UFWSaveGame>(UGameplayStatics::CreateSaveGameObject(UFWSaveGame::StaticClass()));
	}
	return CurrentLoadedSave == nullptr;
}

bool UFWGameInstance::HasLoadedSaveGame() const
{
	return CurrentLoadedSave != nullptr;
}

bool UFWGameInstance::DoesSaveExist(const FString SaveName)
{
	return SaveNames.Get()->SaveNames.Contains(SaveName) && UGameplayStatics::DoesSaveGameExist(SaveName, 0);
}

TArray<FString> UFWGameInstance::SaveNamesArray()
{
	return SaveNames.Get()->SaveNames.Array();
}

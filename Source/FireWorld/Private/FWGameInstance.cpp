// Fill out your copyright notice in the Description page of Project Settings.


#include "FWGameInstance.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Save/FWSaveGame.h"
#include "Save/FWSaveNames.h"
#include "Save/FWUserSettings.h"

UFWGameInstance::UFWGameInstance()
{
}

void UFWGameInstance::Init()
{
	Super::Init();

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
	for (auto It = SaveNames->SaveNames.CreateIterator(); It; ++It)
	{
		if (!DoesSaveExist(*It))
		{
			It.RemoveCurrent();
		}
	}
}

void UFWGameInstance::SaveGame()
{
	if (!CurrentLoadedSave)
	{
		UE_LOG(LogTemp, Error, TEXT("Tried to Save a null LoadedSave"));
		if (!CreateSaveGame(LoadedSaveName))
		{
			return;
		}
	}
	UGameplayStatics::SaveGameToSlot(CurrentLoadedSave, LoadedSaveName, 0);
	bShouldSaveGame = false;
}

void UFWGameInstance::SaveSaveNames()
{
	UGameplayStatics::SaveGameToSlot(SaveNames, SaveNamesName, 0);
}

bool UFWGameInstance::CreateSaveGame(const FString SaveName)
{
	if (SaveNames.Get()->SaveNames.Contains(SaveName))
		return false;
	SaveNames.Get()->SaveNames.Emplace(SaveName);
	ChangeLoadedSaveGame(SaveName);
	SaveGame();
	SaveSaveNames();
	if (CurrentLoadedSave == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create save object in FW Game Instance."));
		return false;
	}
	return true;
}

bool UFWGameInstance::DeleteSaveGame(const FString SaveName)
{
	if (!DoesSaveExist(SaveName))
	{
		return false;
	}
	UGameplayStatics::DeleteGameInSlot(SaveName, 0);
	SaveNames.Get()->SaveNames.Remove(SaveName);
	return true;
}

bool UFWGameInstance::ChangeLoadedSaveGame(const FString SaveName, UFWSaveGame* SaveGame)
{
	if (SaveGame)
	{
		CurrentLoadedSave = SaveGame;
		LoadedSaveName = SaveName;
		return true;
	}
	if (!SaveNames.Get()->SaveNames.Contains(SaveName))
		return false;
	if (CurrentLoadedSave != nullptr)
		UGameplayStatics::SaveGameToSlot(CurrentLoadedSave, LoadedSaveName, 0);
	LoadedSaveName = SaveName;
	if (UGameplayStatics::DoesSaveGameExist(SaveName, 0))
	{
		CurrentLoadedSave = Cast<UFWSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));
	} else
	{
		CurrentLoadedSave = Cast<UFWSaveGame>(UGameplayStatics::CreateSaveGameObject(UFWSaveGame::StaticClass()));
	}
	return CurrentLoadedSave != nullptr;
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

UFWSaveGame* UFWGameInstance::GetSaveGame(const FString SaveName)
{
	if (DoesSaveExist(SaveName))
	{
		USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveName, 0);

		if (!Loaded)
		{
			UE_LOG(LogTemp, Error, TEXT("LoadGameFromSlot returned nullptr"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded class: %s"),
				*Loaded->GetClass()->GetName());

			UFWSaveGame *Save = Cast<UFWSaveGame>(Loaded);

			if (!Save)
			{
				UE_LOG(LogTemp, Error, TEXT("Cast to UFWSaveGame failed."));
			}
			return Save;
		}
	}
	return nullptr;
}

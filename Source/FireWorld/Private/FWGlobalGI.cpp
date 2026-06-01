// Fill out your copyright notice in the Description page of Project Settings.


#include "FWGlobalGI.h"

#include "Save/FWSaveGame.h"

UFWGlobalGI::UFWGlobalGI()
{
	if (DoesSaveExist())
	{
		FWSaveGame = Cast<UFWSaveGame>(UGameplayStatics::LoadGameFromSlot(Name, 0));
		if (FWSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load save object in FW Game Instance."));
		}
	} else
	{
		CreateSaveGame();
	}
}

void UFWGlobalGI::StartGameInstance()
{
	Super::StartGameInstance();

	if (DoesSaveExist())
	{
		FWSaveGame = Cast<UFWSaveGame>(UGameplayStatics::LoadGameFromSlot(Name, 0));
		if (FWSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load save object in FW Game Instance."));
		}
	} else
	{
		CreateSaveGame();
	}
}

void UFWGlobalGI::SaveGame()
{
	if (!FWSaveGame)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Save data not available at save time."));
		UE_LOG(LogTemp, Error, TEXT("Save data not available at save time."));
		if (!CreateSaveGame())
		{
			return;
		}
	}
	UGameplayStatics::SaveGameToSlot(FWSaveGame, Name, 0);
}

bool UFWGlobalGI::CreateSaveGame()
{
	FWSaveGame = Cast<UFWSaveGame>(UGameplayStatics::CreateSaveGameObject(UFWSaveGame::StaticClass()));
	
	if (FWSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create save object in FW Game Instance."));
		return false;
	}
	return true;
}

bool UFWGlobalGI::DoesSaveExist()
{
	return UGameplayStatics::DoesSaveGameExist(Name, 0);
}

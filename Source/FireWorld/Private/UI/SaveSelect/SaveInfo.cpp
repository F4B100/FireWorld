// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaveSelect/SaveInfo.h"

#include "FWGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Save/FWSaveGame.h"

void USaveInfo::NativeConstruct()
{
	Super::NativeConstruct();

	if (!FWGameInstance)
	{
		FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());
	}
	if (MainButton)
	{
		MainButton.Get()->OnClicked.AddDynamic(this, &USaveInfo::MainButtonClicked);
	}
	if (DeleteSaveButton)
	{
		DeleteSaveButton.Get()->OnClicked.AddDynamic(this, &USaveInfo::DeleteSaveButtonClicked);
	}
	LoadSaveInfo(FString());
}

void USaveInfo::LoadSaveInfo(FString SaveToLoad)
{
	if (!FWGameInstance)
	{
		FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());
	}
	if (!SaveToLoad.IsEmpty())
	{
		FWSaveName = SaveToLoad;
		this->SaveName.Get()->SetText(FText::FromString(SaveToLoad));
	}
	if (FWGameInstance)
	{
		FWSaveGame = FWGameInstance->GetSaveGame(FWSaveName);
	}
}

void USaveInfo::MainButtonClicked()
{
	if (FWGameInstance && !FWSaveName.IsEmpty() && FWSaveGame)
	{
		FWGameInstance->ChangeLoadedSaveGame(FWSaveName, FWSaveGame);
		if (LevelToLoad.IsValid() || !LevelToLoad.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad);
		}
	}
}

void USaveInfo::DeleteSaveButtonClicked()
{
	if (FWGameInstance && !FWSaveName.IsEmpty())
	{
		FWGameInstance->DeleteSaveGame(FWSaveName);
	}
}

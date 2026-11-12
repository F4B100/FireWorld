// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaveSelect/FWSaveSelect.h"

#include "FWGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Save/FWSaveGame.h"
#include "Save/FWSaveNames.h"
#include "UI/SaveSelect/FWSaveInfo.h"

void UFWSaveSelect::NativeConstruct()
{
	Super::NativeConstruct();

	FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());

	if (FWGameInstance && FWGameInstance->SaveNames)
	{
		UFWSaveNames *SaveNames = FWGameInstance->SaveNames;
		for (auto Name : SaveNames->SaveNames)
		{
			UFWSaveInfo *NewSave;
			if (SaveInfoClass)
			{
				NewSave = CreateWidget<UFWSaveInfo>(this, SaveInfoClass);
			}
			else
			{
				NewSave = CreateWidget<UFWSaveInfo>(this, UFWSaveInfo::StaticClass());
			}
			NewSave->LevelToLoad = LevelToLoad;
			NewSave->LoadSaveInfo(Name);
			SavesContainer.Get()->AddChild(NewSave);
		}
		FWGameInstance->OnSaveGameAdded.AddUniqueDynamic(this, &UFWSaveSelect::OnSaveGameAdded);
	}
}

void UFWSaveSelect::OnSaveGameAdded(const FString& Name, UFWSaveGame * SaveObject)
{
	UFWSaveInfo *NewSave;
	if (SaveInfoClass)
	{
		NewSave = CreateWidget<UFWSaveInfo>(this, SaveInfoClass);
	}
	else
	{
		NewSave = CreateWidget<UFWSaveInfo>(this, UFWSaveInfo::StaticClass());
	}
	NewSave->LevelToLoad = LevelToLoad;
	NewSave->LoadSaveInfo(Name);
	SavesContainer.Get()->AddChild(NewSave);
}

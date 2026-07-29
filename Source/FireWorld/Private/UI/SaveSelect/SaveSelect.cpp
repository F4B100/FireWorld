// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SaveSelect/SaveSelect.h"

#include "FWGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Save/FWSaveNames.h"
#include "UI/SaveSelect/SaveInfo.h"

void USaveSelect::NativeConstruct()
{
	Super::NativeConstruct();

	FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());
	if (CreateSaveButton)
	{
		CreateSaveButton.Get()->OnClicked.AddDynamic(this, &USaveSelect::OnCreateSaveClicked);
	}

	if (FWGameInstance && FWGameInstance->SaveNames)
	{
		UFWSaveNames *SaveNames = FWGameInstance->SaveNames;
		for (auto Name : SaveNames->SaveNames)
		{
			USaveInfo *NewSave;
			if (SaveInfoClass)
			{
				NewSave = CreateWidget<USaveInfo>(this, SaveInfoClass);
			}
			else
			{
				NewSave = CreateWidget<USaveInfo>(this, USaveInfo::StaticClass());
			}
			NewSave->LevelToLoad = LevelToLoad;
			NewSave->LoadSaveInfo(Name);
			SavesContainer.Get()->AddChild(NewSave);
		}
	}
}

void USaveSelect::OnCreateSaveClicked()
{
	if (SaveName && !SaveName.Get()->GetText().IsEmpty())
	{
		FWGameInstance.Get()->CreateSaveGame(SaveName.Get()->GetText().ToString());
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "option/FWMenuEntry.h"

#include "CommonListView.h"
#include "CommonTextBlock.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"

const TSoftObjectPtr<UFWMenuObject> UFWMenuEntry::GetDataObject() const
{
	return EntryData;
}


void UFWMenuEntry::HandleClicked() const
{
	OnEntrySelected.ExecuteIfBound(EntryData);
}

void UFWMenuEntry::NativeConstruct()
{
	Super::NativeConstruct();
	
	SelectionButton.Get()->OnClicked.AddUniqueDynamic(this, &UFWMenuEntry::HandleClicked);
}

void UFWMenuEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	EntryData = Cast<UFWMenuObject>(ListItemObject);
	if (EntryData->GetEntryData().bIsSpacer)
	{
		SetRenderOpacity(0.0f);
	} else
	{
		SetRenderOpacity(1.0f);
	}
	if (!EntryData.Get()->GetEntryData().Content.IsEmpty())
	{
		TextBlock.Get()->SetText(FText::FromString(EntryData.Get()->GetEntryData().Content));
	}
		else
	{
		
		SetRenderOpacity(0.0f);
	}
}

void UFWMenuEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (EntryData->GetEntryData().SizeEntry > SMALL_NUMBER && EntryData->GetEntryData().SizeEntry != EntrySizeBox->GetWidthOverride())
	{
		EntrySizeBox->SetWidthOverride(EntryData->GetEntryData().SizeEntry);
	}
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Items/FWItem.h"

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UFWItem::CreateSavedItem(FSavedItem& SavedItem)
{
	SavedItem.ItemClass = GetClass();
	SavedItem.SerializedData.Reset();

	FMemoryWriter MemoryWriter(SavedItem.SerializedData);

	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, true);
	Ar.ArIsSaveGame = true;

	Serialize(Ar);
}

void UFWItem::Serialize(FArchive& Ar)
{
	Ar << ItemName;
}

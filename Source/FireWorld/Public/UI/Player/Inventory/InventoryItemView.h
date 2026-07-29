// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "InventoryItemView.generated.h"

class UFWItem;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UInventoryItemView : public UCommonUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName = nullptr;
	UPROPERTY()
	TObjectPtr<UFWItem> Item = nullptr;

	void NativeConstruct() override;

public:
	void SetItem(TObjectPtr<UFWItem> NewItem);
};

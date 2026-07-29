// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/VerticalBox.h"
#include "PlayerInventoryView.generated.h"

class UInventoryItemView;
class UItemManagerComponent;
class AFWPlayerState;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UPlayerInventoryView : public UCommonUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ItemContainer = nullptr;

	UPROPERTY()
	TObjectPtr<AFWPlayerState> PlayerState = nullptr;
	UPROPERTY()
	TObjectPtr<UItemManagerComponent> Inventory = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	TSubclassOf<UInventoryItemView> ItemViewClass = nullptr;

	virtual void NativeConstruct() override;
};

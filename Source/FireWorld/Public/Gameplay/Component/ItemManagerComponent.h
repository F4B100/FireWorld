// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/Items/SavedItem.h"
#include "ItemManagerComponent.generated.h"

struct FSavedInventory;
class UFWGameInstance;
class AFWCharacter;
class UFWItem;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UItemManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemManagerComponent();

	UPROPERTY()
	TObjectPtr<UFWGameInstance> GameInstance = nullptr;

	virtual void BeginPlay() override;
	void LoadInventory(FSavedInventory& Inventory);

	UPROPERTY()
	TObjectPtr<AFWCharacter> Owner;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UFWItem>> Items;

	UFUNCTION(BlueprintCallable)
	UFWItem *GetItem(int32 Index);
	UFUNCTION(BlueprintCallable)
	TArray<UFWItem *> GetAllItems();

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UFWItem*, int32);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, UFWItem*, int32);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemMoved, int32 /*From*/, int32 /*To*/);

	FOnItemAdded OnItemAdded;
	FOnItemRemoved OnItemRemoved;
	FOnItemMoved OnItemMoved;

	UFUNCTION(BlueprintCallable)
	void CollectItem(UFWItem *NewItem);

	UFUNCTION(BlueprintCallable)
	void SaveInventory(FSavedInventory& Inventory);
};

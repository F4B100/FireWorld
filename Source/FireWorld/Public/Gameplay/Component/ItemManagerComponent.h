// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/Items/SavedItem.h"
#include "ItemManagerComponent.generated.h"

class AFWPlayerState;
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
	UPROPERTY()
	TArray<TObjectPtr<UFWItem>> Items = TArray<TObjectPtr<UFWItem>>();

	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AFWCharacter> Owner;

	UFUNCTION(BlueprintCallable)
	UFWItem *GetItem(int32 Index);
	UFUNCTION(BlueprintCallable)
	TArray<UFWItem *> GetAllItems() const;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UFWItem*, int32);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, UFWItem*, int32);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemMoved, int32 /*From*/, int32 /*To*/);

	FOnItemAdded OnItemAdded;
	FOnItemRemoved OnItemRemoved;
	FOnItemMoved OnItemMoved;

	UFUNCTION(BlueprintCallable)
	void CollectItem(UFWItem *NewItem);

	UFUNCTION(BlueprintCallable)
	void SaveInventory(FSavedInventory& Inventory) const;
	UFUNCTION(BlueprintCallable)
	void LoadInventory(FSavedInventory& Inventory);
};

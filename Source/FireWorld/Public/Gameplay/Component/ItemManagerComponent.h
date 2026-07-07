// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/Items/SavedItem.h"
#include "ItemManagerComponent.generated.h"

struct FSavedInventory;
class UFWGlobalGI;
class AFWCharacter;
class UFWItem;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UItemManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemManagerComponent();

	TObjectPtr<UFWGlobalGI> GameInstance = nullptr;

	virtual void BeginPlay() override;
	void LoadInventory(FSavedInventory& Inventory);

	TObjectPtr<AFWCharacter> Owner;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UFWItem>> Items;

	UFUNCTION(BlueprintCallable)
	void CollectItem(UFWItem *NewItem);

	UFUNCTION(BlueprintCallable)
	void SaveInventory(FSavedInventory& Inventory);
};

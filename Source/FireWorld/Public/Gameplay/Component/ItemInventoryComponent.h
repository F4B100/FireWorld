// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInventoryComponent.generated.h"

USTRUCT(Blueprintable)
struct FInventorySpace
{
	GENERATED_BODY()

	FInventorySpace(): Name("default"){}
	explicit FInventorySpace(const FString& Name): Name(Name){}
	
	UPROPERTY(Blueprintable)
	FString Name;
	UPROPERTY(Blueprintable)
	int64 Quantity = 0;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UItemInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemInventoryComponent();
	
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, int64> ItemLocations;
	UPROPERTY(BlueprintReadOnly)
	TArray<FInventorySpace> ItemQuantities;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

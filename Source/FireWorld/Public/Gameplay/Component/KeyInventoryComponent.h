// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KeyInventoryComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UKeyInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UKeyInventoryComponent();
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, bool> Keys;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StablePositionUpdater.generated.h"


class UFWGameInstance;
class UFWSaveGame;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UStablePositionUpdater : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(Blueprintable, VisibleAnywhere, Category = "References", meta = (AllowPrivate))
	TObjectPtr<UFWGameInstance> GameInstance = nullptr;

	UPROPERTY(Blueprintable, VisibleAnywhere, Category = "References", meta = (AllowPrivate))
	TObjectPtr<ACharacter> Owner = nullptr;

public:
	UStablePositionUpdater();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Position)
	FTransform StablePosition = FTransform();

	UPROPERTY(Blueprintable, EditDefaultsOnly, Category = Options)
	FString SavePositionName = FString("Default");

	UPROPERTY(Blueprintable, EditDefaultsOnly, Category = Options)
	FString StableFloorTagName = FString("StableFloor");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Options)
	bool bShouldSetActorInitialPosition = true;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Activate(bool bReset = false) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Position")
	void SetOwnerToStablePosition();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionManager.generated.h"


class AFWCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREWORLD_API UInteractionManagerComponent : public UActorComponent
{
	GENERATED_BODY()


	TObjectPtr<AActor> LastObjectSeen = nullptr;
	TObjectPtr<AActor> CurrentInteractible = nullptr;

	TObjectPtr<AFWCharacter> Owner = nullptr;

	UPROPERTY()
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

public:
	UInteractionManagerComponent();

	TObjectPtr<AActor> GetCurrentInteractible() {return CurrentInteractible;}
	TObjectPtr<AActor> GetLastObjectSeen() {return LastObjectSeen;}
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void CheckForInteractible();
};

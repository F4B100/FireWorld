// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/StablePositionUpdater.h"

#include "FWGlobalGI.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Save/FWSaveGame.h"


// Sets default values for this component's properties
UStablePositionUpdater::UStablePositionUpdater()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UStablePositionUpdater::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("StablePositionUpdater::BeginPlay: Owner could not be set."));
		return;
	}

	GameInstance = Cast<UFWGlobalGI>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("StablePositionUpdater::BeginPlay: GameInstance could not be set."));
		return;
	}
	if (GameInstance.Get()->CurrentLoadedSave)
	{
		if (GameInstance.Get()->CurrentLoadedSave->SavedActorTransforms.Contains(SavePositionName))
			StablePosition = GameInstance.Get()->CurrentLoadedSave->SavedActorTransforms[SavePositionName];
	}
}

void UStablePositionUpdater::Activate(bool bReset)
{
	Super::Activate(bReset);

}

// Called every frame
void UStablePositionUpdater::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner)
	{
		AActor* StandingOnActor = Owner.Get()->GetCharacterMovement()->CurrentFloor.HitResult.GetActor();
		if (StandingOnActor)
		{
			if (StandingOnActor->Tags.Contains(StableFloorTagName))
			{
				StablePosition = Owner.Get()->GetActorTransform();

				GameInstance.Get()->CurrentLoadedSave->SavedActorTransforms.Add(SavePositionName, StablePosition);
				GameInstance.Get()->SaveGame();
			}
		}
	}
}

void UStablePositionUpdater::SetOwnerToStablePosition()
{
	if (Owner)
	{
		Owner.Get()->SetActorTransform(StablePosition);
	}
}


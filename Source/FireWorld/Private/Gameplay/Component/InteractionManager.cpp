// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/InteractionManager.h"

#include "TimerManager.h"
#include "Character/FWCharacter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Gameplay/Interactible/InteractibleActor.h"


UInteractionManager::UInteractionManager()
{
	Owner = Cast<AFWCharacter>(GetOwner());
}


void UInteractionManager::BeginPlay()
{
	Super::BeginPlay();


	FTimerHandle TimerHandle_CheckForInteractible;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ThisClass::CheckForInteractible);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CheckForInteractible, Delegate, 0.05f, true);
}

void UInteractionManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UInteractionManager::CheckForInteractible()
{
	FRotator Rotation = FMath::DegreesToRadians(Owner.Get()->GetControlRotation());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(112451512, 10.0f, FColor::Emerald, Rotation.ToString());
	}

	FHitResult Hit;

	FVector TraceStart = Owner.Get()->GetActorLocation();
	FVector TraceEnd = TraceStart + (Owner.Get()->GetActorForwardVector() * FMath::Cos(Rotation.Pitch) + Owner.Get()->GetActorUpVector() * FMath::Sin(Rotation.Pitch)) * 1000.0f;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, Owner.Get()->GetIgnoreCharacterParams());


	// Uncomment to enable debugging for The Interactable Check

	// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	// UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		LastObjectSeen = Hit.GetActor();
		if (LastObjectSeen && LastObjectSeen->Implements<UInteractibleActor>())
		{
			CurrentInteractible = LastObjectSeen;
			return;
		}
		CurrentInteractible = nullptr;
		// Uncomment to enable debugging for The Interactable Check
		// UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else {
		// Uncomment to enable debugging for The Interactable Check
		// UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		CurrentInteractible = nullptr;
	}
}

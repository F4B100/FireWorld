#include "Gameplay/Component/KeyInventoryComponent.h"


UKeyInventoryComponent::UKeyInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UKeyInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKeyInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


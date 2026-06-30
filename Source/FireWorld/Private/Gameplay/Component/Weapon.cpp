// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Component/Weapon.h"

#include "Components/SphereComponent.h"
#include "Gameplay/Actor/FWProjectile.h"


UWeapon::UWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastFire = FireCooldown;


}


void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(235, 10.0f, FColor::Green, FString::Printf(TEXT("%f\n"), TimeSinceLastFire));
	}
	TimeSinceLastFire += DeltaTime;
	if (TimeSinceLastFire > FireCooldown)
	{
		TimeSinceLastFire = FireCooldown;
		if (bWantsToFire)
		{
			Fire();
		}
	}
}

void UWeapon::Fire()
{
	switch (FiringType)
	{
	case FIRE_SINGLE:
			if (TimeSinceLastFire >= FireCooldown)
			{
				ServerPerformFire();
				TimeSinceLastFire = 0.0f;
			}
		break;
		default:
			UE_LOG(LogActor, Warning, TEXT("No Suitable Firing Type Found"))
	}
}

void UWeapon::ServerPerformFire_Implementation()
{
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetOwner()->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetOwner()->GetInstigator();

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(235, 10.0f, FColor::Green, MuzzleLocation.ToString());
			}
			// Spawn the projectile at the muzzle.
			AFWProjectile* Projectile = World->SpawnActor<AFWProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				Projectile->GetCollisionComponent()->IgnoreActorWhenMoving(GetOwner(), true);

				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Items/ProjectileWeapon.h"

#include "Character/FWCharacter.h"
#include "Components/SphereComponent.h"
#include "Gameplay/Actor/FWProjectile.h"


UProjectileWeapon::UProjectileWeapon()
{
}

void UProjectileWeapon::TickWeapon(float DeltaTime)
{
	Super::TickWeapon(DeltaTime);
	CurrentFiringTime += DeltaTime;
	if (CurrentFiringTime > FiringCooldown && GetWantsToFire())
	{
		ServerPerformFire();
		CurrentFiringTime = 0.0f;
	}
}

void UProjectileWeapon::SwitchedInto(TObjectPtr<AFWCharacter> Character)
{
	Super::SwitchedInto(Character);
}

void UProjectileWeapon::SwitchedOut()
{
	Super::SwitchedOut();
}

void UProjectileWeapon::ServerPerformFire()
{
	Super::ServerPerformFire();
	if (ProjectileClass && OwningCharacter)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		OwningCharacter.Get()->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		const FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		const FRotator MuzzleRotation = CameraRotation;

		if (UWorld* World = GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwningCharacter;
			SpawnParams.Instigator = OwningCharacter->GetInstigator();

			if (AFWProjectile* Projectile = World->SpawnActor<AFWProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams))
			{
				Projectile->GetCollisionComponent()->IgnoreActorWhenMoving(OwningCharacter, true);

				const FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

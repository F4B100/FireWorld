// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Items/ProjectileWeapon.h"

#include "Character/FWCharacter.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "Gameplay/Actor/FWProjectile.h"


UProjectileWeapon::UProjectileWeapon()
{
}

void UProjectileWeapon::TickWeapon(float DeltaTime)
{
	Super::TickWeapon(DeltaTime);
	CurrentFiringTime += DeltaTime;
	if (GEngine)
	{
		FStringFormatOrderedArguments Arguments;
		Arguments.Add(GetWantsToFire());
		GEngine->AddOnScreenDebugMessage(3454879, 10.0f, FColor::Magenta, FString::Format(TEXT("{0}\n"), Arguments));
	}
	if (CurrentFiringTime > FiringCooldown && GetWantsToFire())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(354879, 10.0f, FColor::Magenta, TEXT("Firing\n"));
		}
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

void UProjectileWeapon::ServerPerformFire_Implementation()
{
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

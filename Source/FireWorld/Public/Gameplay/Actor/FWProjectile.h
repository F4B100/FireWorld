// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class FIREWORLD_API AFWProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFWProjectile();

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TObjectPtr<USphereComponent> CollisionComponent;
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TObjectPtr<UStaticMeshComponent> ProjectileMeshComponent;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	USphereComponent* GetCollisionComponent();
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void FireInDirection(const FVector& ShootDirection);
	UFUNCTION()
	void HitSomething(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	                  FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const
	           FHitResult& Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};

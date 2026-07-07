// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actor/FWProjectile.h"

#include "Character/FWCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFWProjectile::AFWProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	if(!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if(!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent.Get()->SetNotifyRigidBodyCollision(true);
		CollisionComponent.Get()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionComponent.Get()->SetGenerateOverlapEvents(true);
		// Set the sphere's collision profile name to "Projectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFWProjectile::HitSomething);
		RootComponent = CollisionComponent;
	}
	if(!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	if(!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Mesh/Sphere/StaticMeshes/Sphere.Sphere'"));
		if(Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}
	ProjectileMovementComponent->SetIsReplicated(true);
	ProjectileMeshComponent->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AFWProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Owner: %s"), *GetNameSafe(GetOwner()));
	UE_LOG(LogTemp, Warning, TEXT("Instigator: %s"), *GetNameSafe(GetInstigator()));
	if (GetInstigator())
	{
		CollisionComponent->IgnoreActorWhenMoving(GetInstigator(), true);
		TArray<AActor*> ChildrenToIgnore = TArray<AActor*>();
		GetInstigator()->GetAllChildActors(ChildrenToIgnore);
		for (auto Component :ChildrenToIgnore)
		{
			CollisionComponent->IgnoreActorWhenMoving(Component, true);
		}
		if (AFWCharacter* Character = Cast<AFWCharacter>(GetInstigator()))
		{
			Character->GetCapsuleComponent()->IgnoreActorWhenMoving(this, true);
		}
	}
}

void AFWProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AFWProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USphereComponent* AFWProjectile::GetCollisionComponent()
{
	return CollisionComponent;
}

void AFWProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFWProjectile::HitSomething(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s hit %s\n"),*this->GetName() , *OtherActor->GetName());
	if (OtherActor != GetInstigator())
	{
		OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
	}
}

void AFWProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
}

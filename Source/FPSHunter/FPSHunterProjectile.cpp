// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSHunterProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSHunterMammal.h"
#include "NiagaraFunctionLibrary.h"



AFPSHunterProjectile::AFPSHunterProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSHunterProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true; // true 면 튀기기, false 면 그대로

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

void AFPSHunterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AFPSHunterMammal* Mammal = Cast<AFPSHunterMammal>(OtherActor);

	if (Mammal)
	{
		AFPSHunterProjectile::Explosion();

		Mammal->Attacked(Attack);
		Destroy();
	}
}

void AFPSHunterProjectile::LifeSpanExpired()
{
	Super::LifeSpanExpired();

	AFPSHunterProjectile::Explosion();
}

void AFPSHunterProjectile::Explosion()
{
	FVector ExplosionLocation = CollisionComp->GetComponentLocation();

	if (BulletExplosionEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletExplosionEffect, ExplosionLocation);
	}

	if (BulletExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BulletExplosionSound, ExplosionLocation);
	}
}
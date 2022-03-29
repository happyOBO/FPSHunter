// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterWeapon.h"
#include "Animation/AnimInstance.h"
#include "FPSHunterCharacter.h"
#include "FPSHunterProjectile.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFPSHunterWeapon::AFPSHunterWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	
	// Hide(true);
}

// Called when the game starts or when spawned
void AFPSHunterWeapon::BeginPlay()
{
	RemainedBullets = TotalBullets;
	Super::BeginPlay();
	
}



void AFPSHunterWeapon::Shoot(FVector const& Location, FRotator const& Rotation)
{
	if (RemainedBullets <= 0) return;

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		World->SpawnActor<AFPSHunterProjectile>(Projectile, Location, Rotation, ActorSpawnParams);
		RemainedBullets--;

		// try and play the sound if specified
		if (ShootSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ShootSound, Location);
		}
	}
}



void AFPSHunterWeapon::Hide(bool bVis)
{
	WeaponMesh->SetVisibility(!bVis);
}

void AFPSHunterWeapon::Load(UAnimInstance* AnimInstance)
{
	if (AnimInstance != nullptr)
	{
		AnimInstance->Montage_Play(LoadAnimation, 1.f);
	}
	
}

void AFPSHunterWeapon::LoadFinish()
{
	RemainedBullets = TotalBullets;
}


int32 AFPSHunterWeapon::GetRemainedBullets()
{
	return RemainedBullets;
}

int32 AFPSHunterWeapon::GetTotalBullets()
{
	return TotalBullets;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSHunterWeapon.generated.h"


class USkeletalMeshComponent;

UCLASS()
class FPSHUNTER_API AFPSHunterWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSHunterWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	TSubclassOf<class AFPSHunterProjectile> Projectile;

	UPROPERTY(EditAnywhere)
	UTexture2D* WeaponThumbnail;

public:
	void Shoot(FVector const& Location, FRotator const& Rotation);
	void Hide(bool bVis);
	void Load();

private:
	UPROPERTY(EditAnywhere, Category = "Bullet")
	int32 NUM_OF_TOTAL_BULLETS;
	int32 RemainedBullets;
	

};

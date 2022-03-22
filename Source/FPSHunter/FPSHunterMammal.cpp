// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammal.h"

// Sets default values
AFPSHunterMammal::AFPSHunterMammal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPSHunterMammal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSHunterMammal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSHunterMammal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPSHunterMammal::Attacked(int attack)
{
	if (0 < _hp) _hp -= attack;
	if (_hp < 0) _hp = 0;
	UE_LOG(LogTemp, Warning, TEXT("hp : %d"), _hp);

}


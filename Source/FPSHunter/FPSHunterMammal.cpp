// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammal.h"
#include "FPSHunterMammalAnim.h"

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

void AFPSHunterMammal::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UFPSHunterMammalAnim>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		// �ش� Montage �� �����ԵǸ� �ش� �Լ��� ȣ���ض�! 
		AnimInstance->OnMontageEnded.AddDynamic(this, &AFPSHunterMammal::OnDeadMontageEnded);
	}
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
	if (IsDead) return;

	if (0 < Hp) Hp -= attack;
	else
	{
		
		if (AnimInstance != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("play Dead Anim"));
			AnimInstance->PlayDeadMontage();
		}

		IsDead = true;
		Hp = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("hp : %d"), Hp);

}

void AFPSHunterMammal::OnDeadMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Hide();
}

void AFPSHunterMammal::Hide()
{
	GetMesh()->SetVisibility(false);
}

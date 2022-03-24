// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammal.h"
#include "FPSHunterMammalAnim.h"
#include "FPSHunterMammalAI.h"

// Sets default values
AFPSHunterMammal::AFPSHunterMammal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Pawn 이 AI 에 의해 조작될때 사용하는 컨트롤러 클래스
	AIControllerClass = AFPSHunterMammalAI::StaticClass();
	// 어떤 상황에서 AI 가 빙의 될 것인지
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Hp = 50;
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
		// 해당 Montage 가 끝나게되면 해당 함수를 호출해라! 
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
		if (AnimInstance != nullptr) AnimInstance->PlayDeadMontage();
		IsDead = true;
		Hp = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("HP : %d"), Hp);
}

void AFPSHunterMammal::OnDeadMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Hide();
}

void AFPSHunterMammal::Hide()
{
	GetMesh()->SetVisibility(false);
}


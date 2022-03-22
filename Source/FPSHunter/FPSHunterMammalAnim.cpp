// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammalAnim.h"

UFPSHunterMammalAnim::UFPSHunterMammalAnim()
{
	UE_LOG(LogTemp, Warning, TEXT("UFPSHunterMammalAnim"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Assets/Animations/Fox/Mammal_Montage_Fox_Dead.Mammal_Montage_Fox_Dead'"));
	if (AM.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DeadMontage apply done"));
		DeadMontage = AM.Object;
		
	}
}

void UFPSHunterMammalAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if (IsValid(pawn))
	{
		Speed = pawn->GetVelocity().Size();
	}
}

void UFPSHunterMammalAnim::PlayDeadMontage()
{
	float rr = Montage_Play(DeadMontage, 2.f);
	UE_LOG(LogTemp, Warning, TEXT("Montage play %f"), rr);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammalAnim.h"
#include "FPSHunterMammal.h"

UFPSHunterMammalAnim::UFPSHunterMammalAnim()
{

}

void UFPSHunterMammalAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UFPSHunterMammalAnim::PlayDeadMontage()
{
	Montage_Play(DeadMontage, 2.f);
}

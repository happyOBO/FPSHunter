// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammalAI.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "FPSHunterMammal.h"

void AFPSHunterMammalAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPSHunterMammalAI::Move, 4.f, true);
}

void AFPSHunterMammalAI::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AFPSHunterMammalAI::Move()
{
	auto CurrentPawn = GetPawn();
	AFPSHunterMammal* Mammal = Cast<AFPSHunterMammal>(CurrentPawn);

	if (Mammal)
	{
		if (Mammal->IsDead) return;
	}


	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 200.f, RandomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
}



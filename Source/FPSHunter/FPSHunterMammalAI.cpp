// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHunterMammalAI.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "FPSHunterMammal.h"

void AFPSHunterMammalAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPSHunterMammalAI::Move, 10.f, true);
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

	UE_LOG(LogTemp, Log, TEXT("Calc RandomLocation"));
	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(CurrentPawn->GetActorLocation(), 2000.f, RandomLocation))
	{
		UE_LOG(LogTemp, Log, TEXT("GetRandomPointInNavigableRadius"));
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
		UE_LOG(LogTemp, Log, TEXT("Calc RandomLocation : %f %f %f"), RandomLocation.Location.X, RandomLocation.Location.Y, RandomLocation.Location.Z);
	}
}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSHunterMammalAI.generated.h"

/**
 * 
 */
UCLASS()
class FPSHUNTER_API AFPSHunterMammalAI : public AAIController
{
	GENERATED_BODY()



	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
private:
	void Move();

private:
	FTimerHandle TimerHandle;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSHunterMammalAnim.generated.h"

/**
 * 
 */
UCLASS()
class FPSHUNTER_API UFPSHunterMammalAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFPSHunterMammalAnim();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DeadMontage;


public:
	void PlayDeadMontage();
	
};

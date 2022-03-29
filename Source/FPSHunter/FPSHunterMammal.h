// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSHunterMammal.generated.h"

class AFPSHunterMammalAI;

UCLASS()
class FPSHUNTER_API AFPSHunterMammal : public ACharacter
{
	GENERATED_BODY()
	friend class AFPSHunterMammalAI;
public:
	// Sets default values for this character's properties
	AFPSHunterMammal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** AnimMontage to play each time we fire */
	UPROPERTY()
	class UFPSHunterMammalAnim* AnimInstance;

	UFUNCTION()
	void OnDeadMontageEnded(UAnimMontage* Montage, bool bInterrupted);


public:
	void Attacked(int attack);
	
	void Hide();

	void Carved(int32& targetCoin);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mammal")
	int Hp;
	UPROPERTY(EditDefaultsOnly, Category = "Mammal")
	int Coin;

	bool IsDead = false;
	bool IsCarved = false;
};

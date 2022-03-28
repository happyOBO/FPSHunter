// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSHunterGameMode.generated.h"

UCLASS(minimalapi)
class AFPSHunterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSHunterGameMode();

protected:
	virtual void BeginPlay() override;


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprint Widgets", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> IngameHUDClass;

	/* 현재 화면에 보여지고 있는 HUD */
	class UUserWidget* CurrentWidget;
};




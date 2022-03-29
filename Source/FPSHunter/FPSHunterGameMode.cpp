// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSHunterGameMode.h"
#include "FPSHunterHUD.h"
#include "FPSHunterCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AFPSHunterGameMode::AFPSHunterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter.BP_FirstPersonCharacter_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHunterHUD::StaticClass();

}

void AFPSHunterGameMode::BeginPlay()
{
	Super::BeginPlay();
	/* get player controller */
	AFPSHunterCharacter* MyCharacter = Cast<AFPSHunterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	/* Set Mouse event and visibility */
	MyController->bShowMouseCursor = false;
	MyController->bEnableClickEvents = true;

	/* À§Á¬ »ý¼º */
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), IngameHUDClass);

	CurrentWidget->AddToViewport();
}

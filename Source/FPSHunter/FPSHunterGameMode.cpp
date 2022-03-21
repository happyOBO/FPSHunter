// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSHunterGameMode.h"
#include "FPSHunterHUD.h"
#include "FPSHunterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSHunterGameMode::AFPSHunterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHunterHUD::StaticClass();
}

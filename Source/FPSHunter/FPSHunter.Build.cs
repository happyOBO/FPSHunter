// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPSHunter : ModuleRules
{
	public FPSHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "NavigationSystem", "AIModule", "GameplayTasks" });
	}
}

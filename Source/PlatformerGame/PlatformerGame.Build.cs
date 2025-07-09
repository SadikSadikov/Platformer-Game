// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlatformerGame : ModuleRules
{
	public PlatformerGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks", "AIModule" });
		
	}
}

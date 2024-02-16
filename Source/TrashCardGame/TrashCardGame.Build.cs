// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TrashCardGame : ModuleRules
{
	public TrashCardGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}

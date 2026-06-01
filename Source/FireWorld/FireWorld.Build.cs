// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FireWorld : ModuleRules
{
	public FireWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG"
		]);

		PrivateDependencyModuleNames.AddRange([
			"Slate",
			"SlateCore",
			"OnlineSubsystem"
		]);
		
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

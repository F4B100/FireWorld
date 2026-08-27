// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FWUI : ModuleRules
{
	public FWUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			[
				ModuleDirectory
				// ... add public include paths required here ...
			]
		);
				
		
		PrivateIncludePaths.AddRange(
			[
				// ... add other private include paths required here ...
			]
		);
			
		
		PublicDependencyModuleNames.AddRange(
			[
				"Core",
				"CommonUI",
				"UMG"
				// ... add other public dependencies that you statically link with here ...
			]
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			[
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			]
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			[
				// ... add any modules that your module loads dynamically here ...
			]
		);
	}
}

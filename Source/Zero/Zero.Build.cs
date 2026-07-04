// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Zero : ModuleRules
{
	public Zero(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]
		{
			"Zero"
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemSteam", "HTTP", "AdvancedSessions"
		});
	}
}

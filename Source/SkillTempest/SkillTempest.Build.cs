// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SkillTempest : ModuleRules
{
	public SkillTempest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"AIModule",
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"InputCore",
				"OnlineSubsystem",
				"OnlineSubsystemSteam",
				"OnlineSubsystemUtils",
				"Slate",
				"SlateCore",
				"UMG"
			});
	}
}
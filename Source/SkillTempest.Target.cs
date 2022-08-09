// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SkillTempestTarget : TargetRules
{
	public SkillTempestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(
			new[]
			{
				"SkillTempest"
			}
		);
	}
}
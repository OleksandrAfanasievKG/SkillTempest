// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SkillTempestEditorTarget : TargetRules
{
	public SkillTempestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange(
			new[]
			{
				"SkillTempest"
			});
	}
}
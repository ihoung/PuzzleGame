// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MagicDetective : ModuleRules
{
	public MagicDetective(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		//PublicIncludePaths.AddRange(new string[] { "MagicDetective/Character", "MagicDetective/Scene", "MagicDetective/UI", "MagicDetective/Level" });
		//PrivateIncludePaths.AddRange(new string[] { "MagicDetective/Character", "MagicDetective/Scene", "MagicDetective/UI", "MagicDetective/Level" });
		AddDirectoriesRecursive(ModuleDirectory);
	}

	private void AddDirectoriesRecursive(string DirectoryPathToSearch)
	{
		PublicIncludePaths.Add(DirectoryPathToSearch);
		PrivateIncludePaths.Add(DirectoryPathToSearch);

		foreach (string DirectoryPath in Directory.GetDirectories(DirectoryPathToSearch))
		{
			PublicIncludePaths.Add(DirectoryPath);
			PrivateIncludePaths.Add(DirectoryPath);
			AddDirectoriesRecursive(DirectoryPath);
		}
	}
}

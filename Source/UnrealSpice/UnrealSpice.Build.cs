// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class UnrealSpice : ModuleRules
{

    // Convenience properties
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public UnrealSpice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Loading in NASA JPL's SPICE library.
        LoadSPICE(Target);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}

    public bool LoadSPICE(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        Log.TraceInformation("Checking SPICE compatibility...");

        // Link the 64-bit MS VISUAL C SPICE library
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            isLibrarySupported = true;
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "cspice64/lib/cspice.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "cspice64/lib/csupport.lib"));
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "cspice64/include"));
            Log.TraceInformation("64-bit SPICE Included.");
        }
        else 
        {
            isLibrarySupported = false;
        }

        // Add a preprocessor definition to determine if the SPICE library was successfully compiled.
        if (isLibrarySupported)
        {
            PublicDefinitions.Add("WITH_SPICE");
        }
        else
        {
            Log.TraceInformation("Platform not compatible with SPICE.");
        }

        return isLibrarySupported;
    }
}

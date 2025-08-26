﻿using UnrealBuildTool;

public class DtApiRequestInfo : ModuleRules
{
    public DtApiRequestInfo(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "DtApiBase", 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "DtApiManager",
                "HTTP",
                
            }
        );
    }
}
using UnrealBuildTool;

public class DtBpAsyncRequest : ModuleRules
{
    public DtBpAsyncRequest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "HTTP", "VaRest"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "DtApiRequestInfo",
            }
        );
    }
}
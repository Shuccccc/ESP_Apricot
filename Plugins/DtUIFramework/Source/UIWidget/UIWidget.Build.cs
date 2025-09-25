using UnrealBuildTool;

public class UIWidget : ModuleRules
{
    public UIWidget(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "DtUIFramework", 
                // Removed "DtUIFramework" to avoid circular dependency
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore" ,
                "UMG", 
                // Added here instead
            }
        );
    }
}
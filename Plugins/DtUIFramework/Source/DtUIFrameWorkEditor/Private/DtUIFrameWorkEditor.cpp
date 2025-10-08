#include "DtUIFrameWorkEditor.h"
#include "ISettingsModule.h" 
#include "ISettingsSection.h"
#include "DtRuntimeUIConfig.h"



#define LOCTEXT_NAMESPACE "FDtUIFrameWorkEditorModule"

void FDtUIFrameWorkEditorModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule)
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"DtUIFramework",
			LOCTEXT("SettingsName", "DtUIFramework"),
			LOCTEXT("DtUIFramework", "Configure settings for the DtUIFramework Plugin."),
			GetMutableDefault<UDtRuntimeUIConfig>()              
		);
	}
}

void FDtUIFrameWorkEditorModule::ShutdownModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "DtUIFramework");
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FDtUIFrameWorkEditorModule, DtUIFrameWorkEditor)
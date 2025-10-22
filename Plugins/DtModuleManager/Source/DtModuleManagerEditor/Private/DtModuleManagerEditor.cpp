#include "DtModuleManagerEditor.h"
#include "DtModuleManagerConfig.h"
#include "ISettingsModule.h"


#define LOCTEXT_NAMESPACE "FDtModuleManagerEditorModule"


void FDtModuleManagerEditorModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule)
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"DtModuleManager",
			LOCTEXT("SettingsName", "DtModuleManager"),
			LOCTEXT("DtModuleManager", "Configure settings for the DtModuleManager Plugin."),
			GetMutableDefault<UDtModuleManagerConfig>()              
		);
	}
}

void FDtModuleManagerEditorModule::ShutdownModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "DtModuleManager");
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FDtModuleManagerEditorModule, DtModuleManagerEditor)
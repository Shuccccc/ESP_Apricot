#include "DtApiBase.h"
#include "DtApiPluginConfig.h"
//#include "Developer/Settings/Public/ISettingsModule.h"
	
#define LOCTEXT_NAMESPACE "FDtApiBaseModule"


void FDtApiBaseModule::StartupModule()
{
	//注册设置
	/*if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project","Plugins", "ApiManager",
			LOCTEXT("ApiManager", "ApiManager"),
			LOCTEXT("ApiManagerDescription", "Settings for ApiManager"),
			GetMutableDefault<UDtApiPluginConfig>()
		);
	}*/
	
}

void FDtApiBaseModule::ShutdownModule()
{
	/*if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "ApiManager");
	}*/
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FDtApiBaseModule, DtApiBase)
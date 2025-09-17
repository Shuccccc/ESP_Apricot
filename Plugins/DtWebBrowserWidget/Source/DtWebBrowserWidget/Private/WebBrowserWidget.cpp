// Copyright Epic Games, Inc. All Rights Reserved.

#include "DtWebBrowserWidget.h"
#include "DtWebBrowserAssetManager.h"
#include "WebBrowserModule.h"
#include "IWebBrowserSingleton.h"
#include "Materials/Material.h"

//////////////////////////////////////////////////////////////////////////
// FWebBrowserWidgetModule

class FDtWebBrowserWidgetModule : public IDtWebBrowserWidgetModule
{
public:
	virtual void StartupModule() override
	{
		if (WebBrowserAssetMgr == nullptr)
		{
			WebBrowserAssetMgr = NewObject<UDtWebBrowserAssetManager>((UObject*)GetTransientPackage(), NAME_None, RF_Transient | RF_Public);
			WebBrowserAssetMgr->LoadDefaultMaterials();

			IWebBrowserModule::Get(); // force the module to load
			if (IWebBrowserModule::IsAvailable() && IWebBrowserModule::Get().IsWebModuleAvailable())
			{
				IWebBrowserSingleton* WebBrowserSingleton = IWebBrowserModule::Get().GetSingleton();
				if (WebBrowserSingleton)
				{
					WebBrowserSingleton->SetDefaultMaterial(WebBrowserAssetMgr->GetDefaultMaterial());
					WebBrowserSingleton->SetDefaultTranslucentMaterial(WebBrowserAssetMgr->GetDefaultTranslucentMaterial());
				}
			}
		}
	}

	virtual void ShutdownModule() override
	{
	}
	
private:
	UDtWebBrowserAssetManager* WebBrowserAssetMgr;
};

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_MODULE(FDtWebBrowserWidgetModule, DtWebBrowserWidget);

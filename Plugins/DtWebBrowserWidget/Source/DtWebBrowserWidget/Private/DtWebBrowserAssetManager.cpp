// Copyright Epic Games, Inc. All Rights Reserved.

#include "DtWebBrowserAssetManager.h"

#if WITH_EDITOR || PLATFORM_ANDROID || PLATFORM_IOS
#include "Materials/Material.h"
#include "WebBrowserTexture.h"
#endif

/////////////////////////////////////////////////////
// WebBrowserAssetManager

UDtWebBrowserAssetManager::UDtWebBrowserAssetManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) ,
	DefaultMaterial(FSoftObjectPath(FString(TEXT("/DtWebBrowserWidget/WebTexture_M.WebTexture_M")))),
	DefaultTranslucentMaterial(FSoftObjectPath(FString(TEXT("/DtWebBrowserWidget/WebTexture_TM.WebTexture_TM"))))
{
#if WITH_EDITOR || PLATFORM_ANDROID || PLATFORM_IOS
	// Add a hard reference to UWebBrowserTexture, without this the WebBrowserTexture DLL never gets loaded on Windows.
	UWebBrowserTexture::StaticClass();

#endif
};

void UDtWebBrowserAssetManager::LoadDefaultMaterials()
{
	DefaultMaterial.LoadSynchronous();
	DefaultTranslucentMaterial.LoadSynchronous();
}

UMaterial* UDtWebBrowserAssetManager::GetDefaultMaterial()
{
	return DefaultMaterial.Get();
}

UMaterial* UDtWebBrowserAssetManager::GetDefaultTranslucentMaterial()
{
	return DefaultTranslucentMaterial.Get();
}

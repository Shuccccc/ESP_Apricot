// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UObject/SoftObjectPtr.h"
#include "Materials/Material.h"
#include "DtWebBrowserAssetManager.generated.h"

class UMaterial;
/**
 * 
 */
UCLASS()
class DTWEBBROWSERWIDGET_API UDtWebBrowserAssetManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void LoadDefaultMaterials();

	UMaterial* GetDefaultMaterial(); 
	UMaterial* GetDefaultTranslucentMaterial(); 

protected:
	UPROPERTY()
	TSoftObjectPtr<UMaterial> DefaultMaterial;
	TSoftObjectPtr<UMaterial> DefaultTranslucentMaterial;
};

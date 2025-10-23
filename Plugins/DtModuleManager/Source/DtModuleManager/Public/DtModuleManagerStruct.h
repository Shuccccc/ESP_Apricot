// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DtModuleBase.h"
#include "DtModuleManagerStruct.generated.h"

/**
 * 
 */
UCLASS()
class DTMODULEMANAGER_API UDtModuleManagerStruct : public UObject
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FSubModuleData
{
	GENERATED_BODY()
    
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Module",ToolTip="模块类"), BlueprintReadWrite, Category = "Module")
	TSubclassOf<ADtModuleBase> Module;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "IsEnabled",ToolTip="是否启用"), BlueprintReadWrite, Category = "isEnabled")
	bool IsEnabled = true;
	
};

USTRUCT(BlueprintType)
struct FModuleDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "Module",ToolTip="模块类"), BlueprintReadWrite, Category = "Module")
	TSubclassOf<ADtModuleBase> Module;

	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "IsEnabled",ToolTip="是否启用"), BlueprintReadWrite, Category = "Module")
	bool IsEnabled = true;
	
	/*
	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "SubModules",ToolTip="子模块"), BlueprintReadWrite, Category = "SubModules")
	TArray<FSubModuleData> SubModules;*/
};
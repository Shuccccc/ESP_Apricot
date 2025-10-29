// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DtModuleToolBase.h"
#include "DtModuleManagerStruct.h"
#include "DtModuleManagerConfig.generated.h"

/**
 * 
 */

UCLASS(config = DtModuleManager, DefaultConfig)
class DTMODULEMANAGER_API UDtModuleManagerConfig : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(config, EditAnywhere, Category = "CoreModules", meta = (DisplayName = "CoreModules"))
	TArray<TSoftClassPtr<UDtModuleToolBase>> CoreModules;

	UPROPERTY(config, EditAnywhere, Category = "ModulesDataTable", meta = (DisplayName = "ModulesDataTable", RequiredAssetDataTags = "RowStructure=/Script/DTModuleManager.ModuleDataTable"))
	TSoftObjectPtr<UDataTable> ModulesDataTable;
};

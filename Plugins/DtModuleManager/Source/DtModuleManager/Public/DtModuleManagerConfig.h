// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TArray<TSubclassOf<ADtModuleBase>> CoreModules;

	UPROPERTY(config, EditAnywhere, Category = "ModulesDataTable", meta = (DisplayName = "ModulesDataTable" , RowType = "FModuleDataTable"))
	TSoftObjectPtr<UDataTable> ModulesDataTable;
	
};

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
struct FModuleDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "Module"), BlueprintReadWrite, Category = "Module")
	TSubclassOf<ADtModuleBase> Module;

	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "IsEnabled"), BlueprintReadWrite, Category = "isEnabled")
	bool IsEnabled = true;
};
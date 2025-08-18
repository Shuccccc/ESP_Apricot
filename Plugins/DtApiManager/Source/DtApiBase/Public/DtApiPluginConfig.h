// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtApiPluginConfig.generated.h"

/**
 * 
 */
UCLASS(Config="ApiManager",DefaultConfig)
class DTAPIBASE_API UDtApiPluginConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TSoftObjectPtr<UDataTable> ApiDataTable;
	
};

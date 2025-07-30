// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtNetModuleConfig.generated.h"

/**
 * 
 */
UCLASS(config = NetModule, defaultconfig)
class DTNETMODULE_API UDtNetModuleConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General Settings", AdvancedDisplay)
	TSoftObjectPtr<UDataTable> ServerAPIDataTable;
};

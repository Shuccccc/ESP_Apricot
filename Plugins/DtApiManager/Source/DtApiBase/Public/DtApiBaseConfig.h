// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtApiBaseConfig.generated.h"

/**
 * 
 */
UCLASS(Config="ApiManager",DefaultConfig)
class DTAPIBASE_API UDtApiBaseConfig : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category = "ApiManager")
	TMap<FName,FString> TestVla;

	
	
};

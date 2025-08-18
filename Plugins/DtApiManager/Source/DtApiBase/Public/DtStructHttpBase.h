// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtStructHttpBase.generated.h"

UENUM(BlueprintType)
enum class EDtHttpMethod : uint8
{
	GET,
	POST,
	PUT,
	DELETE
};

UENUM(BlueprintType)
enum class EDtStreamType : uint8
{
	NONE,
	SSE,
	WEBSOCKET
};

UENUM(BlueprintType)
enum class FDtRequestBody : uint8
{
	JSON,
	FORMDATA,
	FORMURLENCODED
};




/**
 * 
 
UCLASS()
class DTAPIBASE_API UDtStructHttpBase : public UObject
{
	GENERATED_BODY()
};
*/
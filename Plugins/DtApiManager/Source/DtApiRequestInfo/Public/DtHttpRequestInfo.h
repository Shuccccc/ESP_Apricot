// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DtStructHttpBase.h"
#include "UObject/Object.h"
#include "DtHttpRequestInfo.generated.h"

/**
 * 
 */
UCLASS()
class DTAPIREQUESTINFO_API UDtHttpRequestInfo : public UObject
{
	GENERATED_BODY()
public:

	void SenHttpRequest(RequestDataObject& RequestDataObject);
	
};

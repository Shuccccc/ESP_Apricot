// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "VaRestJsonObject.h"
#include "DtStructHttpBase.h"
#include "DtBlueprintHttpRequest.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpDynamicDelegate,  UVaRestJsonObject* , data , int32, StatusCode ,bool,IsSuccess);


UCLASS()
class DTBPASYNCREQUEST_API UDtBlueprintHttpRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable , meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject",DisplayName = "GetDataWithParamter" ))
	static UDtBlueprintHttpRequest* CreateAsyncRequest(UObject* WorldContextObject,FString Url,TMap<FString,FString> Headers,TMap<FString,FString> Params,TMap<FString,FString> Body);

	UPROPERTY(BlueprintAssignable)
	FHttpDynamicDelegate OnCompleted;
	
	virtual void Activate() override;
	
private:
	
	void OnHttpRequestCompleted( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	UDtBlueprintHttpRequest();
	UPROPERTY()
	UObject* M_WorldContextObject;
	
public:
	
	RequestDataObject M_RequestData;
	
	/*UPROPERTY()
	FString M_URL;

	UPROPERTY()
	FString M_RowName;

	UPROPERTY()
	TMap<FString, FString> M_UrlParams;
	
	UPROPERTY()
	TMap<FString,FString> M_Headers;

	UPROPERTY()
	TMap<FString,FString> M_Params;

	UPROPERTY()
	TMap<FString,FString> M_Body;

	UPROPERTY()
	UVaRestJsonObject* M_Json;*/
};

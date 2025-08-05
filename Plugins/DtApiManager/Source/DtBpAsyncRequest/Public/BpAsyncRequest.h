// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpFwd.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BpAsyncRequest.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpDynamicDelegate, bool,IsSuccess, FString,data , int32, StatusCode);


UCLASS()
class DTBPASYNCREQUEST_API UBpAsyncRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable , meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject",DisplayName = "GetDataWithParamter" ))
	static UBpAsyncRequest* CreateAsyncRequest(UObject* WorldContextObject,FString Url,TMap<FString,FString> Headers,TMap<FString,FString> Params,TMap<FString,FString> Body);

	UPROPERTY(BlueprintAssignable)
	FHttpDynamicDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FHttpDynamicDelegate OnFail;
	
	virtual void Activate() override;
	
private:
	
	void OnHttpRequestCompleted( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	UBpAsyncRequest();

	UPROPERTY(Transient)
	UObject* M_WorldContextObject;
	
	UPROPERTY()
	FString M_URL;
	
	UPROPERTY()
	TMap<FString,FString> M_Headers;

	UPROPERTY()
	TMap<FString,FString> M_Params;

	UPROPERTY()
	TMap<FString,FString> M_Body;

	// UPROPERTY()
	// HttpVerb M_Verb = HttpVerb::GET;
};

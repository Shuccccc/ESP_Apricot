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
	
	//创建Http异步请求
	UFUNCTION(BlueprintCallable , meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject",DisplayName = "GetDataWithParamter" ))
	static UBpAsyncRequest* CreateAsyncRequest(UObject* WorldContextObject,FString Url,TMap<FString,FString> Headers,TMap<FString,FString> Params,TMap<FString,FString> Body);

	//成功回调
	UPROPERTY(BlueprintAssignable)
	FHttpDynamicDelegate OnCompleted;
	//失败回调
	UPROPERTY(BlueprintAssignable)
	FHttpDynamicDelegate OnFail;

	//开始异步请求
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

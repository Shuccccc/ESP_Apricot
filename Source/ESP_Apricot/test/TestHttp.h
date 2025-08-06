// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpFwd.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TestHttp.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class HttpVerbDemo : uint8
{
	GET,
	POST,
	PUT,
	DELETE,
	CONNECT 
} ;

USTRUCT(BlueprintType)
struct FHttpRequestParamsDemo
{
	GENERATED_BODY()

	UPROPERTY()
	FString URL;

	UPROPERTY()
	HttpVerbDemo Verb = HttpVerbDemo::GET;  // 添加默认初始化值
	UPROPERTY()
	TMap<FString, FString> Headers;

	UPROPERTY()
	TMap<FString, FString> Params;

	UPROPERTY()
	TMap<FString, FString> Body;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTestHttpDynamicDelegate, bool,IsSuccess, int32, StatusCode, FString,data);

UCLASS()
class ESP_APRICOT_API UTestHttp : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	UTestHttp();

	UFUNCTION(BlueprintCallable , meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject",DisplayName = "TestHttp" ))
	static UTestHttp* TestHttpAsyncAction(UObject* WorldContextObject,
		FString Url ,TMap<FString,FString> Headers, TMap<FString,FString> Params,TMap<FString,FString> Body);

	UPROPERTY(BlueprintAssignable)
	FTestHttpDynamicDelegate OnCompleted;
	
	UPROPERTY(BlueprintAssignable)
	FTestHttpDynamicDelegate OnFail;

	virtual void Activate() override;
	
private:

	void OnHttpRequestCompleted( FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void SendHttp(FString ServerURL);
	
	FString M_URL;
	
	UPROPERTY(Transient)
	UObject* M_WorldContextObject;
	
	HttpVerbDemo M_Verb = HttpVerbDemo::GET;


	UPROPERTY()
	TMap<FString,FString> M_Headers;

	UPROPERTY()
	TMap<FString,FString> M_Params;

	UPROPERTY()
	TMap<FString,FString> M_Body;
};

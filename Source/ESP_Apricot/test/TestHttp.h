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
enum class HttpVerb : uint8
{
	GET,
	POST,
	PUT,
	DELETE,
	CONNECT 
} ;

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTestHttpDynamicDelegate, bool,IsSuccess, int32, StatusCode, FString,data);

UCLASS()
class ESP_APRICOT_API UTestHttp : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	UTestHttp();

	UFUNCTION(BlueprintCallable , meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject",DisplayName = "TestHttp" ))
	static UTestHttp* TestHttpAsyncAction(UObject* WorldContextObject, FString Url , HttpVerb Verb);

	UPROPERTY(BlueprintAssignable)
	FTestHttpDynamicDelegate OnCompleted;
	
	UPROPERTY(BlueprintAssignable)
	FTestHttpDynamicDelegate OnFail;

	virtual void Activate() override;
private:

	void OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnHttpRequestReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void SendHttp(FString ServerURL);
	
	FString M_URL;
	UPROPERTY(Transient)
	UObject* M_WorldContextObject;
	HttpVerb M_Verb = HttpVerb::GET;
};

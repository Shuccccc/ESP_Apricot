// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TestHttp.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETestHttp : uint8
{
	testhttp UMETA(DisplayName = "testhttp"),
	Local UMETA(DisplayName = "Local"),
	MaxNum UMETA(Hidden)
} ;

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FTestHttpDynamicDelegate, bool,IsSuccess, int32, StatusCode, FString,Message, FGuid, AsyncID);

UCLASS()
class ESP_APRICOT_API UTestHttp : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	UTestHttp();

	UFUNCTION(BlueprintCallable , meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject",DisplayName = "TestHttp" ))
	static UTestHttp* TestHttpAsyncAction(UObject* WorldContextObject, ETestHttp TestHttp);

	UPROPERTY(BlueprintAssignable)
	FTestHttpDynamicDelegate OnCompleted;
	
	UPROPERTY(BlueprintAssignable)
	FTestHttpDynamicDelegate OnFail;





	
private:

	
};

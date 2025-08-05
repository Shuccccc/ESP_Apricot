// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ApiBaseStruct.generated.h"

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

UENUM(BlueprintType)
enum class EDtContentType : uint8
{
	JSON,
	FORMDATA,
	FORMURLENCODED
};
USTRUCT(BlueprintType)
struct FHttpRequestParams
{
	GENERATED_BODY()

	UPROPERTY()
	FString URL;

	UPROPERTY()
	HttpVerb Verb;

	UPROPERTY()
	TMap<FString, FString> Headers;

	UPROPERTY()
	TMap<FString, FString> Params;

	UPROPERTY()
	TMap<FString, FString> Body;
};

USTRUCT(BlueprintType)
struct FApiDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,meta = (Display = "Api"), BlueprintReadWrite, Category = "Table")
	FString Value;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求类型"), BlueprintReadWrite, Category = "Table")
	HttpVerb RequestType;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "平台"), BlueprintReadWrite, Category = "Table")
	FName PlatForm;
	
	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求数据类型"), BlueprintReadWrite, Category = "Table")
	EDtContentType ContentType;
	
	UPROPERTY(EditDefaultsOnly, meta = (Display = "备注"), BlueprintReadWrite, Category = "Table")
	FString Marks;
	
};

USTRUCT()
struct FServerConfig
{
	GENERATED_BODY()

	UPROPERTY(DisplayName="Protocol")
	FString Protocol;

	UPROPERTY(DisplayName="ServerIp")
	FString ServerIp;

	UPROPERTY(DisplayName="ServerPort")
	FString ServerPort;

	UPROPERTY(DisplayName="ConfigRoute")
	FString ConfigRoute;

	UPROPERTY(DisplayName="AppId")
	FString AppId;

	UPROPERTY(DisplayName="AppSecret")
	FString AppSecret;

	UPROPERTY(DisplayName="CServerIp")
	FString CServerIp;

	UPROPERTY(DisplayName="UserIp")
	FString UserIp;

};

UCLASS()
class DTAPIBASE_API UApiBaseStruct : public UObject
{
	GENERATED_BODY()
};

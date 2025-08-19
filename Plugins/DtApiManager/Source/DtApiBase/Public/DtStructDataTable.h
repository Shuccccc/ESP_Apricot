// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DtStructHttpBase.h"
#include "DtStructDataTable.generated.h"

USTRUCT()
struct FApiDataInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString ApiName;
	UPROPERTY()
	FString ApiUrl;
	UPROPERTY()
	EDtHttpMethod ApiMethod;
	UPROPERTY()//
	FString ServerIP;
	UPROPERTY()
	FDtRequestBody ApiParamType;
	
};

USTRUCT(BlueprintType)
struct FHttpRequestParams
{
	GENERATED_BODY()

	UPROPERTY()
	FString URL;

	UPROPERTY()
	EDtHttpMethod Verb = EDtHttpMethod::GET;

	UPROPERTY()
	TMap<FString, FString> Headers;

	UPROPERTY()
	TMap<FString, FString> Params;

	UPROPERTY()
	TMap<FString, FString> Body;
};

USTRUCT(BlueprintType)
struct FIpDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Table")
	FString Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Table")
	FString Marks;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "私有化部署键值"), BlueprintReadWrite, Category = "Table")
	FString PrivateKey;
};

USTRUCT(BlueprintType)
struct FApiDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,meta = (Display = "Api"), BlueprintReadWrite, Category = "Table")
	FString Value;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求类型"), BlueprintReadWrite, Category = "Table")
	EDtHttpMethod Verb = EDtHttpMethod::GET;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "平台"), BlueprintReadWrite, Category = "Table")
	FName PlatForm;
	
	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求数据类型"), BlueprintReadWrite, Category = "Table")
	FDtRequestBody ContentType = FDtRequestBody::JSON;
	
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
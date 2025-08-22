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

UENUM(BlueprintType)
enum class EDtAuthorization : uint8
{
	None UMETA(DisplayName = "无验签(None)"),
	
	Industry UMETA(DisplayName = "工业互联网总接口(Industry)"),
	
	IndustryAbility UMETA(DisplayName = "工业互联网能力系统(IndustryAbility)"),
	
	Business UMETA(DisplayName = "业务系统(IndustryAbility)"),
	
	Plugins UMETA(DisplayName = "插件平台(IndustryAbility)"),
	
	BasicAuth UMETA(DisplayName = "BasicAuth"),
	
	BearerToken UMETA(DisplayName = "BearerToken"),
};

USTRUCT(BlueprintType)
struct FApiDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,meta = (DisplayName = "Api"), BlueprintReadWrite, Category = "Table")
	FString Value;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "请求类型"), BlueprintReadWrite, Category = "Table")
	EDtHttpMethod Verb = EDtHttpMethod::GET;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "平台"), BlueprintReadWrite, Category = "Table")
	FString PlatForm;
	
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "请求数据类型"), BlueprintReadWrite, Category = "Table")
	FDtRequestBody ContentType = FDtRequestBody::JSON;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "验签"), BlueprintReadWrite, Category = "Table")
	EDtAuthorization Authorization = EDtAuthorization::None;
	
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "备注"), BlueprintReadWrite, Category = "Table")
	FString Marks;
	
};

USTRUCT(BlueprintType)
struct FIpDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Table", meta = (DisplayName = "Value"))
	FString Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Table", meta = (DisplayName = "PrivateKey"))
	FString PrivateKey;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Table", meta = (DisplayName = "Marks"))
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
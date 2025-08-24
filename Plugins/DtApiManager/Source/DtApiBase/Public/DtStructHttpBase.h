// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interfaces/IHttpRequest.h"
#include "DtStructHttpBase.generated.h"

class UVaRestJsonObject;


DECLARE_DELEGATE_ThreeParams( FDtHttpRequestCallbackStruct ,FHttpRequestPtr, FHttpResponsePtr,bool)
UENUM(BlueprintType)
enum class EDtHttpMethod : uint8
{
	GET,
	POST,
	PUT,
	DELETE
};

UENUM(BlueprintType)
enum class EDtStreamType : uint8
{
	NONE,
	SSE,
	WEBSOCKET
};

UENUM(BlueprintType)
enum class FDtRequestBody : uint8
{
	JSON,
	FORMDATA,
	FORMURLENCODED
};

struct RequestDataObject {
	FString AppendUrl;
	//DataTable行键值
	FString RowKey;
	//请求地址前缀
	FString PrefixUrl;
	//header参数集合
	TMap<FString, FString> HeaderParams;
	//url参数集合
	TMap<FString, FString> UrlParams;
	//body参数集合
	TMap<FString, FString> BodyParams;
	//body json集合
	UVaRestJsonObject* BodyJsonObject;
	//回调对象指针
	UObject* Object;
	//回调对象方法
	FDtHttpRequestCallbackStruct CallBack;
};


/**
 * 
 
UCLASS()
class DTAPIBASE_API UDtStructHttpBase : public UObject
{
	GENERATED_BODY()
};
*/
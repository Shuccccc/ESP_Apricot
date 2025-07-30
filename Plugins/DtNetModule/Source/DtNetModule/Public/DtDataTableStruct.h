// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtDataTableStruct.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDtRequestType : uint8
{
	GET,
	POST,
	PUT,
	DELETE,
};

UENUM(BlueprintType)
enum class EDtContentType : uint8
{
	JSON,
	FORMDATA,
	FORMURLENCODED
};

USTRUCT(BlueprintType)
struct FApiDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,meta = (Display = "Api"), BlueprintReadWrite, Category = "Table")
	FString Value;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求类型"), BlueprintReadWrite, Category = "Table")
	EDtRequestType RequestType;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "平台"), BlueprintReadWrite, Category = "Table")
	FName PlatForm;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "备注"), BlueprintReadWrite, Category = "Table")
	FString Marks;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "需要缓存的body参数,多个参数用,分割"), BlueprintReadWrite, Category = "Table")
	FString CacheBodyParams;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "需要缓存的url参数,多个参数用,分割"), BlueprintReadWrite, Category = "Table")
	FString CacheUrlParams;

	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求此接口后继续请求的接口,多个接口用,分割"), BlueprintReadWrite, Category = "Table")
	FString AfterKeys;
	
	UPROPERTY(EditDefaultsOnly, meta = (Display = "请求数据类型"), BlueprintReadWrite, Category = "Table")
	EDtContentType ContentType;



};
UCLASS()
class DTNETMODULE_API UDtDataTableStruct : public UObject
{
	GENERATED_BODY()
};

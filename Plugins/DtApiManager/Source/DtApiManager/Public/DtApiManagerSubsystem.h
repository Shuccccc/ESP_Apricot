// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DtApiManagerDefault.h"
#include "DtStructHttpBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtApiManagerSubsystem.generated.h"

/**
 * 
 */


enum class EApiDataCacheType : uint8;

UCLASS()
class DTAPIMANAGER_API UDtApiManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
 
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

//Blueprint

	// 初始化数据表
	UFUNCTION(BlueprintCallable, Category = "DtApiManager")
	void InitApiDataTable(UDataTable *ApiConfigTable,UDataTable *ServerIpTable);
	
	// 初始化配置文件和本地平台地址
	UFUNCTION(BlueprintCallable, Category = "DtApiManager", meta=(DisplayName="初始化本地平台地址"))
	bool InitDefaultPlatform();

	// 从服务平台获取平台地址
	UFUNCTION(BlueprintCallable, Category = "DtApiManager",meta=(DisplayName="请求平台地址"))
	void InitPlatformIp();

	//添加头
	UFUNCTION(BlueprintCallable, Category = "DtApiManager")
	void AddCacheData(EApiDataCacheType Type,FString Value);
	

private:

	UPROPERTY()
	UDataTable* M_ApiConfigDataTable ;
	UPROPERTY()
	UDataTable* M_ServerIpDataTable ;

	UPROPERTY()
	TMap<FString,FString> M_PlatformConfigINI;
	
	UPROPERTY()
	TMap<FString,FString> M_PlatformIpMap;
	
	//登陆后需要初始化的 里面有 loginToken 密钥等
	UPROPERTY()
	TMap<FString,FString> CacheDataMap;

	//
	TMap<FString, FString> GetIndustryAbility();
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FString GetPlatformKey(FName RowKey);

	static FString GetSHA256Signature(FString  String) ;

public:
//处理配置
	
	FString GetApiUrlForKey(RequestDataObject& object, bool& bSucces);

	bool GetHeaderForKey(RequestDataObject& object, bool& bSucces);
	
	FString GetVerbForKey(RequestDataObject& object);

	TMap<FString, FString> AppendContentType(RequestDataObject& object) ;
	

	FString GetContent(RequestDataObject& object);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtApiManagerSubsystem.generated.h"

/**
 * 
 */


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

	// 从服务平台获取平台地址
	UFUNCTION(BlueprintCallable, Category = "DtApiManager")
	void InitPlatformIp(UDataTable *ApiConfigTable,UDataTable *ServerIpTable);
	
	// 初始化配置文件和本地平台地址
	UFUNCTION(BlueprintCallable, Category = "DtApiManager", meta=(DisplayName="初始化平台地址"))
	bool InitDefaultPlatform();

private:
	UPROPERTY()
	TMap<FString,FString> M_PlatformConfigINI;
	UPROPERTY()
	UDataTable* M_ApiConfigDataTable ;
	UPROPERTY()
	UDataTable* M_ServerIpDataTable ;
	UPROPERTY()
	TMap<FString,FString> M_PlatformIpMap;

	//登陆后需要初始化的 里面有 loginToken 密钥等
	UPROPERTY()
	TMap<FString,FString> CacheDataMap;

	//
	TMap<FString, FString> GetIndustryAbility();
};

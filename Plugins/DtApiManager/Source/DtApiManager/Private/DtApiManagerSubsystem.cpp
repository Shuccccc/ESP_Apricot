// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"

#include "DtApiManagerDefault.h"

bool UDtApiManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UDtApiManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


}

void UDtApiManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UDtApiManagerSubsystem::InitApiManager(UDataTable* ApiConfigTable)
{
	if (InitDefaultPlatform())
	{
		
	}
}

bool UDtApiManagerSubsystem::InitDefaultPlatform()
{
	FConfigFile tDefaultPlatform;
	tDefaultPlatform.Read(DtApiManagerConfig::GetApiConfigIni());
	if (tDefaultPlatform.IsEmpty())
	{
		return false;
	}
	ConfigMap = {
		{TEXT("Protocol"), TEXT("")},
		{TEXT("ServerIp"), TEXT("")},
		{TEXT("ServerPort"), TEXT("")},
		{TEXT("ConfigRoute"), TEXT("")},
		{TEXT("AppId"), TEXT("")},
		{TEXT("AppSecret"), TEXT("")},
		{TEXT("CServerIp"), TEXT("")},
		{TEXT("UserIp"), TEXT("")}
	};
	
	FString temString;
	
	for (auto i : ConfigMap)
	{
		if (tDefaultPlatform.GetString(TEXT("PlatformConfig"), *i.Key, temString))
		{
			i.Value=temString;
			UE_LOG(LogTemp, Log, TEXT("初始化配置列表: %s = %s"), *i.Key, *i.Value)
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("初始化配置列表失败: %s"), *i.Key)
		}
	}
	return true;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"
#include "DtStructDataTable.h"
#include "DtApiManagerDefault.h"

bool UDtApiManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UDtApiManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//初始化PlatformMap
	TArray<FString> ConfigKeys = PlatformConfigKeys::GetAllPlatformConfigKeys();
	for (const FString& Key : ConfigKeys)
	{
		M_PlatformConfigMap.Add(Key, TEXT(""));
	}
}

void UDtApiManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UDtApiManagerSubsystem::InitApiManager(UDataTable* ApiDataTable,UDataTable *ServerIpTable)
{
	//初始化配置文件
	InitDefaultPlatform();
	
	//初始化数据表
	if ( !ApiDataTable && !ServerIpTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: APIDataTable Init :: UDataTable* is not valid"));
		return;
	}
	
	if ( ApiDataTable->GetRowStruct() != FApiDataTable::StaticStruct() && ServerIpTable->GetRowStruct() != FIpDataTable::StaticStruct())
	{
		UE_LOG(LogTemp, Error, TEXT("Error: APIDataTable Init :: DataTable structure type check failed"));
		return;
	}
	
	M_ApiConfigDataTable = ApiDataTable;
	M_ServerIpDataTable = ServerIpTable; 

	//初始化平台地址
	// @TODO 优化栈顶冒火 注释赎罪券+1
	
	namespace Key =  PlatformConfigKeys;
	
	FString TempString = *M_PlatformConfigMap.Find(Key::ConfigRoute);
	FString PrivatePlatformUrl;

	if (*M_PlatformConfigMap.Find(Key::CServerIp) != FString{TEXT("")})
	{
		PrivatePlatformUrl = *M_PlatformConfigMap.Find(Key::CServerIp) +"/app-api" + TempString;
	}
	else
	{
		PrivatePlatformUrl = *M_PlatformConfigMap.Find(Key::Protocol) + "://" + *M_PlatformConfigMap.Find(Key::ServerIp) + ":" + *M_PlatformConfigMap.Find(Key::ServerPort) + TempString;
	}
	//处理ServerIpDataTable
	TArray<FIpDataTable*> RowMap;
	M_ServerIpDataTable->GetAllRows("GetRowMap", RowMap);

	for (auto i : RowMap)
	{
		UE_LOG(LogTemp, Error, TEXT("他奶奶滴看看Key %s") , *i->PrivateKey);
	}
}

bool UDtApiManagerSubsystem::InitDefaultPlatform()
{
	FConfigFile tDefaultPlatform;
	if ( ! FPaths::FileExists(DtApiManagerConfig::GetApiConfigIni()))
	{
		UE_LOG(LogTemp, Error, TEXT("Error: InitDefaultPlatform :: DefaultPlatform.ini is not valid"));
		return false;
	}
	tDefaultPlatform.Read(DtApiManagerConfig::GetApiConfigIni());
	
	FString temString;
	
	for (auto i : M_PlatformConfigMap)
	{
		if (tDefaultPlatform.GetString(TEXT("PlatformConfig"), *i.Key, temString))
		{
			i.Value=temString.Replace(TEXT(":/"), TEXT("://"));;
			UE_LOG(LogTemp, Log, TEXT("初始化配置列表: %s = %s"), *i.Key, *i.Value)
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("初始化配置列表失败: %s"), *i.Key)
		}
	}
	return true;
}

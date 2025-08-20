// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"
#include "DtStructDataTable.h"
#include "DtApiManagerDefault.h"
#include "Http.h"

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

void UDtApiManagerSubsystem::InitApiManager(UDataTable* ApiDataTable,UDataTable *ServerIpTable)
{

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

	for (FIpDataTable* i : RowMap)
	{
		PrivatePlatformUrl.Append(i->PrivateKey+",");
	}
	//请求地址
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
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

	//初始化PlatformMap
	
	namespace Name =  PlatformNames;
	namespace Key =  PlatformConfigKeys;
	
	M_PlatformConfigMap.Empty();
	FString temString;
	
	TArray<FString> ConfigKeys = Key::GetAllPlatformConfigKeys();
	for ( FString& Key : ConfigKeys)
	{
		if (tDefaultPlatform.GetString(TEXT("PlatformConfig"), *Key, temString))
		{
			M_PlatformConfigMap.Add(Key,temString.Replace(TEXT(":/"), TEXT("://")));

			UE_LOG(LogTemp, Log, TEXT("初始化配置列表: %s = %s"),*Key, *temString.Replace(TEXT(":/"), TEXT("://")) )
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("初始化配置列表失败: %s"), *Key)
		}
	}

	//初始化平台地址
	M_PlatformIpMap.Add(Name::IndustryPlatform, *M_PlatformConfigMap.Find(Key::CServerIp));
	M_PlatformIpMap.Add(Name::UserInfoPlatform, *M_PlatformConfigMap.Find(Key::UserIp));
	M_PlatformIpMap.Add(Name::PluginPlatform,*M_PlatformConfigMap.Find(Key::Protocol)+"://"+*M_PlatformConfigMap.Find(Key::ServerIp)+":"+*M_PlatformConfigMap.Find(Key::ServerPort));

	for (auto i : M_PlatformIpMap)
	{
		UE_LOG(LogTemp, Log, TEXT("初始化平台地址 : %s == %s"), *i.Key , *i.Value);
	}
	return true;
}

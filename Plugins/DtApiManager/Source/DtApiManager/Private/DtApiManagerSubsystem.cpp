// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"
#include "DtStructDataTable.h"
#include "DtApiManagerDefault.h"
#include "Http.h"

#define TEST 1

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


void UDtApiManagerSubsystem::InitApiDataTable(UDataTable* ApiDataTable,UDataTable *ServerIpTable)
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
}

void UDtApiManagerSubsystem::InitPlatformIp(UDataTable* ApiConfigTable, UDataTable* ServerIpTable)
{
	//初始化平台地址
	// @TODO 优化栈顶冒火
	
	namespace Key =  PlatformConfigKeys;
	
	FString TempString = *M_PlatformConfigINI.Find(Key::ConfigRoute);
	FString PrivatePlatformUrl;

	if (*M_PlatformConfigINI.Find(Key::CServerIp) != FString{TEXT("")})
	{
		PrivatePlatformUrl = *M_PlatformConfigINI.Find(Key::CServerIp) +"/app-api" + TempString;
	}
	else
	{
		PrivatePlatformUrl = *M_PlatformConfigINI.Find(Key::Protocol) + "://" + *M_PlatformConfigINI.Find(Key::ServerIp) + ":" + *M_PlatformConfigINI.Find(Key::ServerPort) + TempString;
	}
	//处理ServerIpDataTable
	TArray<FIpDataTable*> RowMap;
	M_ServerIpDataTable->GetAllRows("GetRowMap", RowMap);

	for (FIpDataTable* i : RowMap)
	{
		PrivatePlatformUrl.Append(i->PrivateKey+",");
	}
	// @TODO 妈的怎么这么多东西
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
	
	M_PlatformConfigINI.Empty();
	FString temString;
	
	TArray<FString> ConfigKeys = Key::GetAllPlatformConfigKeys();
	
	for ( FString& i : ConfigKeys)
	{
		tDefaultPlatform.GetString(TEXT("PlatformConfig"), *i, temString);

		M_PlatformConfigINI.Add(i,temString.Replace(TEXT(":/"), TEXT("://")));

		UE_LOG(LogTemp, Log, TEXT("初始化配置列表: %s = %s"),*i, *temString.Replace(TEXT(":/"), TEXT("://")) )
	}

	//初始化平台地址
	M_PlatformIpMap.Add(Name::IndustryPlatform, *M_PlatformConfigINI.Find(Key::CServerIp));
	M_PlatformIpMap.Add(Name::UserInfoPlatform, *M_PlatformConfigINI.Find(Key::UserIp));
	M_PlatformIpMap.Add(Name::PluginPlatform,*M_PlatformConfigINI.Find(Key::Protocol)+"://"+*M_PlatformConfigINI.Find(Key::ServerIp)+":"+*M_PlatformConfigINI.Find(Key::ServerPort));

#if TEST
	for (auto i : M_PlatformIpMap)
	{
		UE_LOG(LogTemp, Log, TEXT("初始化平台地址 : %s == %s"), *i.Key , *i.Value);
	}
#endif
	
	return true;
}

TMap<FString, FString> UDtApiManagerSubsystem::GetIndustryAbility()
{
	TMap<FString, FString> HeaderParameter;

	//FromLocalConfig
	FString AppIdValue = *M_PlatformConfigINI.Find(PlatformConfigKeys::AppId);
	FString SecretKeyValue = *M_PlatformConfigINI.Find(PlatformConfigKeys::AppSecret);
	//FromGenerated
	FString NonceString = FGuid::NewGuid().ToString();
	FString TimeString = FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S"));
	//FromDefault
	FString OrganIdString;
	
	HeaderParameter.Add(PlatformHeaders::AppIdHeaderName , AppIdValue);
	HeaderParameter.Add(PlatformHeaders::SecretKeyName , SecretKeyValue);
	
	HeaderParameter.Add(PlatformHeaders::NonceName , NonceString);
	HeaderParameter.Add(PlatformHeaders::TimeStampName , TimeString);





	return HeaderParameter;
	
}

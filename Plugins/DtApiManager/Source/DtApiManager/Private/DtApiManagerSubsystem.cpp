// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"
#include "DtStructDataTable.h"
#include "DtApiManagerDefault.h"
#include "Http.h"
#include "EncryptionContextOpenSSL.h"
#include "Json.h"
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

void UDtApiManagerSubsystem::InitPlatformIp()
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
	auto HeaderParameter = GetIndustryAbility();
	//请求
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(PrivatePlatformUrl);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"),HttpContentType::Json);
	FString temLogStr = TEXT("Request Header : {");
	for (auto i : HeaderParameter)
	{
		Request->AppendToHeader(i.Key, i.Value);
		temLogStr.Append(i.Key).Append(TEXT("\":\""));
		temLogStr.Append(i.Value).Append(TEXT("\","));
	}
	temLogStr.Append(TEXT("\"}"));
	Request->OnProcessRequestComplete().BindUObject(this,&UDtApiManagerSubsystem::OnHttpResponse);
	UE_LOG(LogTemp, Log, TEXT("远端平台地址Request URL : %s "), *PrivatePlatformUrl);
	UE_LOG(LogTemp, Log, TEXT("远端平台地址Request Verb : GET"));
	UE_LOG(LogTemp, Log, TEXT("远端平台地址Request Header : %s "), *temLogStr);
	Request->ProcessRequest();
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
	//FromBackend
	M_PlatformIpMap.Add(PlatformHeaders::OrganIdName,TEXT("1483809126285927348"));
	FString OrganIdString = *M_PlatformIpMap.Find(PlatformHeaders::OrganIdName);
	//FromGenerated
	FString DataToSign = AppIdValue + NonceString + TimeString + OrganIdString + SecretKeyValue;
	/*FSHA256Signature Signature;
	FGenericPlatformMisc::GetSHA256Signature(&DataToSign,DataToSign.GetAllocatedSize(),Signature);*/
	FString SignString ; 
	
	FEncryptionContextOpenSSL CryptoContext;
	FTCHARToUTF8 ConvertedString(*DataToSign);
	TArrayView<const uint8> DataView(reinterpret_cast<const uint8*>(ConvertedString.Get()), ConvertedString.Length());
	TArray<uint8> Hash;
	CryptoContext.CalcSHA256(DataView , Hash);
	for (uint8 Byte : Hash)
	{
		SignString += FString::Printf(TEXT("%02x"), Byte);
	}
	 
	
	HeaderParameter.Add(PlatformHeaders::AppIdHeaderName , AppIdValue);
	HeaderParameter.Add(PlatformHeaders::SecretKeyName , SecretKeyValue);
	
	HeaderParameter.Add(PlatformHeaders::NonceName , NonceString);
	HeaderParameter.Add(PlatformHeaders::TimeStampName , TimeString);
	HeaderParameter.Add(PlatformHeaders::OrganIdName , OrganIdString);

	HeaderParameter.Add(PlatformHeaders::SignName , SignString);

	return HeaderParameter;
}

void UDtApiManagerSubsystem::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr FHttpRequestPtr, bool bWasSuccessful)
{
	FString RequestStr = FHttpRequestPtr->GetContentAsString();
	
	UE_LOG(LogTemp, Log, TEXT("远端平台地址Response : %s "), *RequestStr);
	auto JsonReader = TJsonReaderFactory<>::Create(RequestStr);
	
	TSharedPtr<FJsonObject> JsonObject;
	
	if ( ! FJsonSerializer::Deserialize(JsonReader,JsonObject))
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR 初始化平台地址 :: 解析Json失败"));
	}
	auto JsonData = JsonObject->GetObjectField(FStringView{TEXT("data")});
	
	auto RowNames = M_ServerIpDataTable->GetRowNames();
	
	FIpDataTable* temRow;
	
	for (auto i : RowNames)
	{
		temRow = M_ServerIpDataTable->FindRow<FIpDataTable>(i,i.ToString()) ;

		FString TemRowName = i.ToString();
		FString TemRowPrivateKey = JsonData->GetStringField(temRow->PrivateKey);
		
		M_PlatformIpMap.Add(TemRowName, TemRowPrivateKey);
		UE_LOG(LogTemp, Log, TEXT("从远端初始化平台地址 : %s == %s"), *TemRowName, *TemRowPrivateKey);
	}
	/*
	int index = 0;
	for (auto * i : RowNameArray)
	{
		M_PlatformIpMap.Add(RowNames[index].ToString() ,  JsonData->GetStringField(i->PrivateKey));
		UE_LOG(LogTemp, Log, TEXT("测试顺序能不能对上之 Key = %s  Val= %s"), *RowNames[index].ToString(), *JsonData->GetStringField(i->PrivateKey));
		index++;
	}
	*/
}

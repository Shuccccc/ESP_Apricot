// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"
#include "DtStructDataTable.h"
#include "Http.h"
#include "EncryptionContextOpenSSL.h"
#include "Json.h"
#include "VaRestJsonObject.h"
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
	PrivatePlatformUrl.Append(PlatformHeaders::UserAppId+",");
	PrivatePlatformUrl.Append(PlatformHeaders::UserAppSecret);
	
	auto HeaderParameter = GetIndustryAbility();
	//请求
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(PrivatePlatformUrl);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"),HttpContentType::Json);
	
//-------------------------PrintLog
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
//-------------------------PrintLog
	
	Request->ProcessRequest();
}

void UDtApiManagerSubsystem::AddCacheData(EApiDataCacheType Type, FString Value)
{
	FString Key;
	switch (Type) {
	case EApiDataCacheType::OrganId:
	{
		Key = PlatformHeaders::OrganIdName;
	}
		break;
	case EApiDataCacheType::Token:
	{
		Key = PlatformHeaders::TokenName ;
		break;
	}
	}
	if (CacheDataMap.Contains(Key))
	{
		CacheDataMap.Remove(Key);
	}
	
	CacheDataMap.Add(Key,Value);
}


TMap<FString, FString> UDtApiManagerSubsystem::GetIndustryAbility()
{
	TMap<FString, FString> HeaderParameter;

	//FromLocalConfig
	//FromLocalConfig
	FString AppIdValue = *M_PlatformConfigINI.Find(PlatformConfigKeys::AppId);
	FString SecretKeyValue = *M_PlatformConfigINI.Find(PlatformConfigKeys::AppSecret);
	//FromGenerated
	FString NonceString = FGuid::NewGuid().ToString();
	FString TimeString = FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S"));
	//FromDefault
	//FromBackend
	
	//M_PlatformIpMap.Add(PlatformHeaders::OrganIdName,TEXT("1483809126285927348"));
	
	FString OrganIdString = *CacheDataMap.Find(PlatformHeaders::OrganIdName);
	//FromGenerated
	FString DataToSign = AppIdValue + NonceString + TimeString + OrganIdString + SecretKeyValue;

//-------------------------GetSHA256Signature
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
//-------------------------GetSHA256Signature
	
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
	//初始化密钥
	if (JsonData->HasField(PlatformHeaders::UserAppId) && JsonData->HasField(PlatformHeaders::UserAppSecret))
	{
		CacheDataMap.Add(JsonData->GetStringField(PlatformHeaders::UserAppId),JsonData->GetStringField(PlatformHeaders::UserAppSecret));
	}

}

FString UDtApiManagerSubsystem::GetPlatformKey(FName RowKey)
{
	FApiDataTable *temRow = M_ApiConfigDataTable->FindRow<FApiDataTable>(RowKey,RowKey.ToString(),true);
	return *M_PlatformIpMap.Find(temRow->PlatForm);
}

FString UDtApiManagerSubsystem::GetSHA256Signature(FString String)
{
	FString SignString ; 
	FEncryptionContextOpenSSL CryptoContext;
	FTCHARToUTF8 ConvertedString(*String);
	TArrayView<const uint8> DataView(reinterpret_cast<const uint8*>(ConvertedString.Get()), ConvertedString.Length());
	TArray<uint8> Hash;
	CryptoContext.CalcSHA256(DataView , Hash);
	for (uint8 Byte : Hash)
	{
		SignString += FString::Printf(TEXT("%02x"), Byte);
	}
	return SignString;
}

FString UDtApiManagerSubsystem::GetApiUrlForKey(RequestDataObject& object, bool& bSucces ) 
{
	
	FApiDataTable *temRow = M_ApiConfigDataTable->FindRow<FApiDataTable>(FName{object.RowKey},object.RowKey,true);
	
	FString ApiUrl = *M_PlatformIpMap.Find(temRow->PlatForm);
	
	ApiUrl.Append(temRow->Value);
	
	for (auto& Kvp : object.UrlParams)
	{
		if (Kvp.Key.IsEmpty())
		{
			continue;
		}
		if (!ApiUrl.Contains("?"))
		{
			ApiUrl.Append("?");
		}
		else
		{
			ApiUrl.Append("&");
		}
		ApiUrl.Append(*Kvp.Key);
		ApiUrl.Append("=");
		ApiUrl.Append(*Kvp.Value);
	}
	bSucces = true;
	return ApiUrl;
}

bool UDtApiManagerSubsystem::GetHeaderForKey(RequestDataObject& object, bool& bSucces)
{
	//GetInitData(FName(PlatformConfigKeys::AppId), bSuccess)
	
	FString AppIdValue = *M_PlatformConfigINI.Find(PlatformConfigKeys::AppId);
	FString NonceString = FGuid::NewGuid().ToString();
	FString TimeString = FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S"));

	object.HeaderParams.Add(PlatformHeaders::AppIdHeaderName, AppIdValue);
	object.HeaderParams.Add(PlatformHeaders::NonceName, NonceString);
	object.HeaderParams.Add(PlatformHeaders::TimeStampName, TimeString);

	FString SecretKeyValue = *M_PlatformConfigINI.Find(PlatformConfigKeys::AppSecret);
	
	FApiDataTable *temRow = M_ApiConfigDataTable->FindRow<FApiDataTable>(FName{object.RowKey},object.RowKey,true);
	
	EDtAuthorization Authorization = temRow->Authorization;

	switch (Authorization)
	{
	case EDtAuthorization::None:
	{
		break;
	}
	case EDtAuthorization::Industry:
	{
		FString OrganIdString = PlatformHeaders::OrganIdDefault;
		object.HeaderParams.Add(PlatformHeaders::OrganIdName, OrganIdString);
		FString SignString = GetSHA256Signature(AppIdValue + NonceString + TimeString + OrganIdString + SecretKeyValue);
		object.HeaderParams.Add(PlatformHeaders::SignName, SignString);
		
		break;
	}
	case EDtAuthorization::IndustryAbility:
	{
		FString OrganIdString;

		if (!object.HeaderParams.Contains(PlatformHeaders::OrganIdName))
		{
			if (CacheDataMap.Contains(PlatformHeaders::OrganIdName))
			{
				FString OrganId = *CacheDataMap[PlatformHeaders::OrganIdName];
			}
		}
		else
		{
			OrganIdString = object.HeaderParams[PlatformHeaders::OrganIdName];
		}
		object.HeaderParams.Add(PlatformHeaders::OrganIdName, OrganIdString);
		FString SignString =  GetSHA256Signature(AppIdValue + NonceString + TimeString+ OrganIdString + SecretKeyValue);
		object.HeaderParams.Add(PlatformHeaders::SignName, SignString);
		break;
	}

	case EDtAuthorization::Business:
	{
		FString SignString =GetSHA256Signature(AppIdValue + NonceString + TimeString + SecretKeyValue);
		object.HeaderParams.Add(PlatformHeaders::SignName, SignString);
		break;
	}

	case EDtAuthorization::Plugins:
	{
		FString SignString = GetSHA256Signature(AppIdValue + NonceString + TimeString + SecretKeyValue);
		object.HeaderParams.Add(PlatformHeaders::AuthorizationName, SignString);
		break;
	}

	case EDtAuthorization::BasicAuth:
		break;
	case EDtAuthorization::BearerToken:
	{
		FString tokenObjecl;
		if (CacheDataMap.Contains(PlatformHeaders::TokenName))
		{
			tokenObjecl = *CacheDataMap[PlatformHeaders::TokenName];
		}
		FString tokenObject =TEXT("");
		//HeaderParameter.Add(AuthorizationName,  tokenObject.StringValue);
		object.HeaderParams.Add(PlatformHeaders::AuthorizationName, "Bearer " + tokenObject);
		break;
	}
	}

	return true;
}

FString UDtApiManagerSubsystem::GetVerbForKey(RequestDataObject& object)
{
	FApiDataTable *temRow = M_ApiConfigDataTable->FindRow<FApiDataTable>(FName{object.RowKey},object.RowKey,true);

	switch (temRow->Verb) {
	case EDtHttpMethod::GET:
		return TEXT("GET");
	case EDtHttpMethod::POST:
		return TEXT("POST");
	case EDtHttpMethod::PUT:
		return TEXT("PUT");
	case EDtHttpMethod::DELETE:
		return TEXT("DELETE");
	}
	
	return TEXT("GET");;
}

TMap<FString, FString> UDtApiManagerSubsystem::AppendContentType(RequestDataObject& object)
{
	TMap<FString, FString> ContentType;
	FApiDataTable *temRow = M_ApiConfigDataTable->FindRow<FApiDataTable>(FName{object.RowKey},object.RowKey,true);

	switch (temRow->ContentType) {
	case FDtRequestBody::JSON:
		
		object.HeaderParams.Add(HttpContentType::TypeName,HttpContentType::Json);
		return ContentType;
	case FDtRequestBody::FORMDATA:
		object.HeaderParams.Add(HttpContentType::TypeName,HttpContentType::FormData);
		return ContentType;
	case FDtRequestBody::FORMURLENCODED:
		object.HeaderParams.Add(HttpContentType::TypeName,HttpContentType::FormUrlencoded);
		return ContentType;
	default:
		object.HeaderParams.Add(HttpContentType::TypeName,HttpContentType::Json);
		return object.HeaderParams;
	}

}

FString UDtApiManagerSubsystem::GetContent(RequestDataObject& object)
{
	if ( object.BodyParams.Num() > 0)
	{
	 object.BodyJsonObject->SetMapFields_string(object.BodyParams);
	}
	return object.BodyJsonObject->EncodeJsonToSingleString();
}

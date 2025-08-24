#pragma once

namespace DtApiManagerConfig
{
	inline FString GetApiConfigPath() 
	{
		return FPaths::ProjectDir() + TEXT("Config/private/"); 
	}
    
	inline FString GetApiConfigIni() 
	{ 
		return GetApiConfigPath() + TEXT("DefaultPlatform.ini"); 
	}
	
}
// 平台配置键名常量
namespace PlatformConfigKeys
{
	inline const FString Protocol = TEXT("Protocol");
	inline const FString ServerIp = TEXT("ServerIp");
	inline const FString ServerPort = TEXT("ServerPort");
	inline const FString ConfigRoute = TEXT("ConfigRoute");
	inline const FString AppId = TEXT("AppId");
	inline const FString AppSecret = TEXT("AppSecret");
	inline const FString CServerIp = TEXT("CServerIp");
	inline const FString UserIp = TEXT("UserIp");

	inline TArray<FString> GetAllPlatformConfigKeys()
	{
		return {
			PlatformConfigKeys::Protocol,
			PlatformConfigKeys::ServerIp,
			PlatformConfigKeys::ServerPort,
			PlatformConfigKeys::ConfigRoute,
			PlatformConfigKeys::AppId,
			PlatformConfigKeys::AppSecret,
			PlatformConfigKeys::CServerIp,
			PlatformConfigKeys::UserIp
		};
	}
};
namespace PlatformNames
{
	inline const FString IndustryPlatform = TEXT("工业互联网平台");
	inline const FString UserInfoPlatform = TEXT("用户信息平台");
	inline const FString PluginPlatform = TEXT("插件平台");
}

namespace PlatformHeaders
{
	inline const FString AppIdName = TEXT("appid");
	inline const FString SecretKeyName = TEXT("secretkey");
	inline const FString AppIdHeaderName = TEXT("APPID");
	inline const FString NonceName = TEXT("NONCE");
	inline const FString TimeStampName = TEXT("TIMESTAMP");
	inline const FString NodeCodeName = TEXT("NODECODE");
	inline const FString OrganIdName = TEXT("ORGANID");
	inline const FString SignName = TEXT("SIGN");
	inline const FString NodeCodeDefault = TEXT("");
	inline const FString OrganIdDefault = TEXT("1");
	inline const FString UserAppId = TEXT("user.appid");//暂时意义不明 先加上
	inline const FString UserAppSecret = TEXT("user.appsecret");//暂时意义不明 先加上
}
namespace HttpContentType
{
	// JSON数据
	inline const FString Json = TEXT("application/json");
	// 表单数据
	inline const FString FormUrlencoded = TEXT("application/x-www-form-urlencoded");
	// 多部分表单数据
	inline const FString FormData = TEXT("multipart/form-data");
	// 纯文本
	inline const FString Text = TEXT("text/plain");
	// 二进制数据
	inline const FString Binary = TEXT("application/octet-stream");
}

#pragma once

namespace DtApiManagerConfig
{
	inline  FString GetApiConfigPath() 
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
	constexpr const TCHAR* Protocol = TEXT("Protocol");
	constexpr const TCHAR* ServerIp = TEXT("ServerIp");
	constexpr const TCHAR* ServerPort = TEXT("ServerPort");
	constexpr const TCHAR* ConfigRoute = TEXT("ConfigRoute");
	constexpr const TCHAR* AppId = TEXT("AppId");
	constexpr const TCHAR* AppSecret = TEXT("AppSecret");
	constexpr const TCHAR* CServerIp = TEXT("CServerIp");
	constexpr const TCHAR* UserIp = TEXT("UserIp");

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
	constexpr const TCHAR* IndustryPlatform = TEXT("工业互联网平台");
	constexpr const TCHAR* UserInfoPlatform = TEXT("用户信息平台");
	constexpr const TCHAR* PluginPlatform = TEXT("插件平台");
}

namespace PlatformHeaders
{
	constexpr const TCHAR* AppIdName = TEXT("appid");
	constexpr const TCHAR* SecretKeyName = TEXT("secretkey");
	constexpr const TCHAR* AppIdHeaderName = TEXT("APPID");
	constexpr const TCHAR* NonceName = TEXT("NONCE");
	constexpr const TCHAR* TokenName = TEXT("TOKEN");
	constexpr const TCHAR* TimeStampName = TEXT("TIMESTAMP");
	constexpr const TCHAR* NodeCodeName = TEXT("NODECODE");
	constexpr const TCHAR* OrganIdName = TEXT("ORGANID");
	constexpr const TCHAR* SignName = TEXT("SIGN");
	constexpr const TCHAR* NodeCodeDefault = TEXT("");
	constexpr const TCHAR* OrganIdDefault = TEXT("1");
	constexpr const TCHAR* AuthorizationName = TEXT("Authorization");
	constexpr const TCHAR* UserAppId = TEXT("user.appid");//暂时意义不明 先加上
	constexpr const TCHAR* UserAppSecret = TEXT("user.appsecret");//暂时意义不明 先加上
}
namespace HttpContentType
{
	constexpr const TCHAR* TypeName = TEXT("Content-Type");
	// JSON数据
	constexpr const TCHAR* Json = TEXT("application/json");
	// 表单数据
	constexpr const TCHAR* FormUrlencoded = TEXT("application/x-www-form-urlencoded");
	// 多部分表单数据
	constexpr const TCHAR* FormData = TEXT("multipart/form-data");
	// 纯文本
	constexpr const TCHAR* Text = TEXT("text/plain");
	// 二进制数据
	constexpr const TCHAR* Binary = TEXT("application/octet-stream");
}

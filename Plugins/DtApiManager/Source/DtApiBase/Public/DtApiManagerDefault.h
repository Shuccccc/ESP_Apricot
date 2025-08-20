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
#pragma once

namespace DtApiManagerConfig
{
	// 使用函数方式提供配置路径
	inline FString GetApiConfigPath() 
	{
		return FPaths::ProjectDir() + TEXT("Config/private/"); 
	}
    
	inline FString GetApiConfigIni() 
	{ 
		return GetApiConfigPath() + TEXT("DefaultPlatform.ini"); 
	}
}
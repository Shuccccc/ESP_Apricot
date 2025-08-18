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
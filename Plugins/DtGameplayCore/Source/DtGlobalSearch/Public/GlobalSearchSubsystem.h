// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GlobalSearchSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DTGLOBALSEARCH_API UGlobalSearchSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	/**
	 * @param GlobalSearchObject 注册全局搜索的对象
	 * @param GlobalSearchName 注册全局搜索的名称
	 * @param GlobalSearchDescription 全局搜索对象描述
	 */
	void RegisterToGlobalSearch(UObject* GlobalSearchObject, FString GlobalSearchName , FString GlobalSearchDescription);

	void UnRegisterFromGlobalSearch(UObject* M_GlobalSearchObject, FString M_GlobalSearchName);
	
	static TSubclassOf<UObject> GlobalSearchByName( FString Name);

private:

	TMap<FString, TSubclassOf<UObject>> GlobalSearchMap;
	
};

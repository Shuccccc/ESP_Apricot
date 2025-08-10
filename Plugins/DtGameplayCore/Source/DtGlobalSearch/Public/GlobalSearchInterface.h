// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GlobalSearchInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGlobalSearchInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DTGLOBALSEARCH_API IGlobalSearchInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * @param GlobalSearchObject 注册全局搜索的对象
	 * @param GlobalSearchName 注册全局搜索的名称
	 * @param GlobalSearchDescription 全局搜索对象描述
	 */
	virtual	void RegisterToGlobalSearch(UObject* GlobalSearchObject, FString GlobalSearchName , FString GlobalSearchDescription) = 0;

	virtual void UnRegisterFromGlobalSearch(UObject* M_GlobalSearchObject, FString M_GlobalSearchName) = 0;
	
private:
	
	int32 GlobalSearchGuid = 0 ;

	FString M_GlobalSearchName ;
	
	FString M_GlobalSearchDescription ;
};

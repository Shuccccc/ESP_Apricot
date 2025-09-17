// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleManagerSubsystemTest.h"
#include "ModuleBaseActor.h"
#include "Engine/AssetManager.h"

/*
void UModuleManagerSubsystemTest::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	/*FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	
	FSoftObjectPath AssetPath(TEXT("/Game/ESafetyPlatform_Content/Module"));
	
	StreamableManager.RequestAsyncLoad(
		TArray<FSoftObjectPath>{AssetPath},
		FStreamableDelegate::CreateUObject(this, &UModuleManagerSubsystemTest::AsyncLoadCompleted),
		FStreamableManager::DefaultAsyncLoadPriority,
		true,
		false,
		TEXT("ModuleManagerSubsystem")
	);#1#
}
*/

AModuleBaseActor* UModuleManagerSubsystemTest::GetModuleFromClass(TSubclassOf<AModuleBaseActor> ModuleClass)
{
	if (!ModuleClass)
	{
		return nullptr;
	}
	
	for (AModuleBaseActor* ModuleActor : ModuleList)
	{
		if (ModuleActor && ModuleActor->GetClass() == ModuleClass.Get())
		{
			return ModuleActor;
		}
	}
	return nullptr;
}


void UModuleManagerSubsystemTest::AsyncLoadCompleted()
{
//获取所有继承自AModuleBaseActor的类
	TArray<UClass*> ModuleBaseClassArray;
	GetDerivedClasses(AModuleBaseActor::StaticClass(),ModuleBaseClassArray , true);
	
	if (ModuleBaseClassArray.Num() == 0)
	{
		return;
	}
//剔除骨架蓝图和未实现方法的蓝图
	ModuleBaseClassArray.RemoveAll([&](const UClass* P_Class)
	{
		FString tem_name = P_Class->GetName();
		return !P_Class->IsFunctionImplementedInScript(TEXT("InitModule")) || tem_name.StartsWith(TEXT("SKEL")) ||tem_name.StartsWith(TEXT("REINST"));
	});
	
//CDO
	for (auto Class : ModuleBaseClassArray)
	{
		if (Class && !Class->HasAnyClassFlags(CLASS_Abstract))
		{
			Class->GetDefaultObject();
		}
	}
	auto World = GetWorld();
	for (auto* I_Class : ModuleBaseClassArray)                                                         
	{
		auto T_ModuleBasePtr =World->SpawnActor<AModuleBaseActor>(I_Class);
		ModuleList.Emplace(T_ModuleBasePtr);
		T_ModuleBasePtr->InitModule();
	}
	
}

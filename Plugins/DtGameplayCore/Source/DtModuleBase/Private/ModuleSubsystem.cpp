// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleSubsystem.h"

bool UModuleSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UModuleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UModuleSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<AModuleBaseActor*> UModuleSubsystem::InitModule()
{
/*
	//获取所有派生类
	TArray<UClass*> ModuleBaseClassArray;
	GetDerivedClasses(AModuleBaseActor::StaticClass(),ModuleBaseClassArray , true);
	
	//剔除骨架蓝图和未实现接口的蓝图
	ModuleBaseClassArray.RemoveAll([&](const UClass* P_Class)
	{
		return !P_Class->IsFunctionImplementedInScript(TEXT("InitializeModule")) || P_Class->GetName().StartsWith(TEXT("SKEL"));
	});

	auto World = AActor::GetWorld();
	for (auto* I_Class : ModuleBaseClassArray)                                                         
	{
		auto T_ModuleBasePtr =World->SpawnActor<AModuleBaseActor>(I_Class);
		ModuleActors.Emplace(T_ModuleBasePtr);
		AModuleBaseActor::Execute_InitializeModule(T_ModuleBasePtr);
	}
*/
	return ModuleActors;
	
}

AModuleBaseActor* UModuleSubsystem::GetModule(TSubclassOf<AModuleBaseActor> ModuleClass)
{
	for (auto i : ModuleActors)  
	{
		if (ModuleClass.Get() == i->GetClass())
		{
			return i;  
		}
	}
	return nullptr;
}

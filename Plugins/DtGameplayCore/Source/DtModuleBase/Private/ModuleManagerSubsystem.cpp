// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleManagerSubsystem.h"
#include "Engine/AssetManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StreamableManager.h"

void UModuleManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UModuleManagerSubsystem::ForceLoadBlueprints()
{
	bool babala = true;
	if (babala)
	{
		
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;
	Filter.PackagePaths.Add(TEXT("/Game/ESafetyPlatform_Content/Module"));
	Filter.bRecursivePaths = true;

	TArray<FAssetData> Assets;
	AssetRegistry.GetAssets(Filter, Assets);

	for (const FAssetData& Asset : Assets)
	{
		if (!Asset.IsAssetLoaded())
		{
			Asset.GetAsset();
		}
	}
	}

	if (!babala)
	{
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	
		TArray<FString> AssetPaths;
		AssetPaths.Add(TEXT("/Game/ESafetyPlatform_Content/Module"));

		// 异步加载整个目录的资源
		TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(AssetPaths, FStreamableDelegate::CreateLambda([this]() {
			// 资源加载完成
		}), 0, false);
	}

}

TArray<AModuleBaseActor*> UModuleManagerSubsystem::InitModuleSubsystem()
{
	if (ModuleActors.Num() > 0)
	{
		for (auto i : ModuleActors)
		{
			i->Destroy();
		}
		ModuleActors.Empty();
	}
	ForceLoadBlueprints();
	//获取所有派生类
	TArray<UClass*> ModuleBaseClassArray;

	GetDerivedClasses(AModuleBaseActor::StaticClass(),ModuleBaseClassArray , true);
	if (ModuleBaseClassArray.Num() == 0)
	{
		return TArray<AModuleBaseActor*>();
	}
	//剔除骨架蓝图和未实现方法的蓝图
	ModuleBaseClassArray.RemoveAll([&](const UClass* P_Class)
	{
		FString tem_name = P_Class->GetName();
		return !P_Class->IsFunctionImplementedInScript(TEXT("InitModule")) || tem_name.StartsWith(TEXT("SKEL")) ||tem_name.StartsWith(TEXT("REINST"));
	});

	auto World = GetWorld();
	for (auto* I_Class : ModuleBaseClassArray)                                                         
	{
		auto T_ModuleBasePtr =World->SpawnActor<AModuleBaseActor>(I_Class);
		ModuleActors.Emplace(T_ModuleBasePtr);
		T_ModuleBasePtr->InitModule();
	}

	return ModuleActors;
	
}

AModuleBaseActor* UModuleManagerSubsystem::GetModule(TSubclassOf<AModuleBaseActor> ModuleClass) 
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


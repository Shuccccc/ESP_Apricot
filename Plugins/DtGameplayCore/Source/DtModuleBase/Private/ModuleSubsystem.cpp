// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleSubsystem.h"
#include "Engine/AssetManager.h"
#include "AssetRegistry/AssetRegistryModule.h"

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
void UModuleSubsystem::ForceLoadBlueprints()
{
	if (false)
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

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	
	// 创建资源路径列表
	TArray<FString> AssetPaths;
	AssetPaths.Add(TEXT("/Game/ESafetyPlatform_Content/Module"));

	// 异步加载整个目录的资源
	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(AssetPaths, FStreamableDelegate::CreateLambda([]() {
		// 加载完成后的回调，这里可以执行一些后续操作
		UE_LOG(LogTemp, Log, TEXT("Module blueprints async loaded"));
	}), 0, false);
}

TArray<AModuleBaseActor*> UModuleSubsystem::InitModuleSubsystem()
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

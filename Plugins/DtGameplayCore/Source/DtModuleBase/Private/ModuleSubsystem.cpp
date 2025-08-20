// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleSubsystem.h"

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
//#if WITH_EDITOR
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
//#endif
}

TArray<AModuleBaseActor*> UModuleSubsystem::InitModuleSubsystem()
{
	
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleManagerSubsystemBase.h"

//#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"
//#include "Engine/StreamableManager.h"
#include "Engine/Engine.h"

void UModuleManagerSubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnPostLoadMapHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UModuleManagerSubsystemBase::OnPostLoadMap);
}
//弃置
void UModuleManagerSubsystemBase::ForceLoadBlueprints()
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

void UModuleManagerSubsystemBase::OnPostLoadMap(UWorld* World)
{
	RequestAsyncModuleLoad(World);
	
}

void UModuleManagerSubsystemBase::RequestAsyncModuleLoad(UWorld* WorldContext)
{
    // 同步发现所有模块资产（此过程很快，因为它读取的是缓存）
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter Filter;
    Filter.PackagePaths.Add(TEXT("/Game/ESafetyPlatform_Content/Module"));
    Filter.bRecursivePaths = true;
	Filter.ClassPaths.Add(AModuleBaseActor::StaticClass()->GetClassPathName());
    TArray<FAssetData> Assets;
    AssetRegistryModule.Get().GetAssets(Filter, Assets);

    if (Assets.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("ModuleManager: No module assets found to load."));
        return;
    }

    // 收集需要异步加载的资产路径
    TArray<FSoftObjectPath> PathsToLoad;
    for (const FAssetData& Asset : Assets)
    {
        PathsToLoad.Add(Asset.ToSoftObjectPath());
    }

    UE_LOG(LogTemp, Log, TEXT("ModuleManager: Requesting async load of %d modules."), PathsToLoad.Num());
    
    //使用StreamableManager提交异步加载请求
    FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
    TWeakObjectPtr<UWorld> WeakWorldContext = WorldContext;

    StreamableManager.RequestAsyncLoad(PathsToLoad, FStreamableDelegate::CreateUObject(this,&UModuleManagerSubsystemBase::AsyncLoadModuleAsset, WeakWorldContext, PathsToLoad));
}

void UModuleManagerSubsystemBase::AsyncLoadModuleAsset(TWeakObjectPtr<UWorld> WeakWorldContext,TArray<FSoftObjectPath> PathsToLoad)
{
	if (!WeakWorldContext.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("ModuleManager: Module load completed, but World is no longer valid."));
		return;
	}
	UWorld* World = WeakWorldContext.Get();
        
	UE_LOG(LogTemp, Log, TEXT("ModuleManager: Module assets loaded. Spawning actors..."));

	//遍历已加载的资源，生成Actor实例
	for (const FSoftObjectPath& Path : PathsToLoad)
	{
		UClass* LoadedClass = Cast<UClass>(Path.ResolveObject());
		if (!LoadedClass) continue;
            
		// 过滤掉骨架蓝图和未实现InitModule的蓝图
		const FString ClassName = LoadedClass->GetName();
		if (ClassName.StartsWith(TEXT("SKEL_")) || ClassName.StartsWith(TEXT("REINST_"))) continue;
		if (!LoadedClass->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(AModuleBaseActor, InitModule))) continue;
            
		if (AModuleBaseActor* SpawnedModule = World->SpawnActor<AModuleBaseActor>(LoadedClass))
		{
			ModuleMap.Emplace(LoadedClass, SpawnedModule);
			SpawnedModule->InitModule();
			UE_LOG(LogTemp, Log, TEXT("ModuleManager: Spawned and initialized module: %s"), *SpawnedModule->GetName());
		}
	}
}

//弃置
TArray<AModuleBaseActor*> UModuleManagerSubsystemBase::InitModuleSubsystem()
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

AModuleBaseActor* UModuleManagerSubsystemBase::GetModule(TSubclassOf<AModuleBaseActor> ModuleClass) 
{

	return ModuleMap.FindRef(ModuleClass);
	/*for (auto i : ModuleActors)  
	{
		if (ModuleClass.Get() == i->GetClass())
		{
			return i;  
		}
	}
	return nullptr;*/
}


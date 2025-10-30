// Fill out your copyright notice in the Description page of Project Settings.


#include "DtModuleManagerSubsystem.h"
#include "DtModuleManagerConfig.h"
#include "DtModuleManagerStruct.h"
#include "DtModuleBase.h"
#include "DtModuleToolBase.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"


void UDtModuleManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
//    Collection.InitializeDependency<UDtUIEventBroker>();
    Super::Initialize(Collection);
    
    
    	OnWorldLoadedDelegateHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDtModuleManagerSubsystem::OnWorldLoaded);
    
}

void UDtModuleManagerSubsystem::OnWorldLoaded(UWorld* NewWorld)
{
    //@TODO 后续转到BeginPlay模块

    FString CurrentMapName = UGameplayStatics::GetCurrentLevelName(NewWorld);
    const FString StartupMapName = TEXT("M_Startup");

    if (!CurrentMapName.Equals(StartupMapName, ESearchCase::IgnoreCase))
    {
        UE_LOG(LogTemp, Log, TEXT("Main map '%s' detected! Starting Core UI initialization..."), *CurrentMapName);

        LoadModules();
    }
}

void UDtModuleManagerSubsystem::LoadModules()
{
const auto Setting = GetDefault<UDtModuleManagerConfig>();
    
    if (!Setting)
    {
       UE_LOG(LogTemp, Error, TEXT("UDtModuleManagerSubsystem::LoadModules: Failed to get settings!"));
       return;
    }

    // 加载核心模块 
    TArray<FSoftObjectPath> AssetsToLoad;
    
    if (!Setting->CoreModules.IsEmpty())
    {
       for (const auto& CoreModule : Setting->CoreModules)
       {
           if (!CoreModule.IsNull())
           {
               AssetsToLoad.Add(CoreModule.ToSoftObjectPath());
           }
       }
    }

    //加载配置表
    UDataTable* LoadedTable = Setting->ModulesDataTable.LoadSynchronous();

    
    if (LoadedTable)
    {
        static const FString ContextString(TEXT("Collecting M_Modules From DataTable"));
        
        TArray<FName> RowNames = LoadedTable->GetRowNames();
        
        for (const FName& RowName : RowNames)
        {
            FModuleDataTable* RowData = LoadedTable->FindRow<FModuleDataTable>(RowName , ContextString);
            
            if (RowData && !RowData->Module.IsNull())
            {
                AssetsToLoad.Add(RowData->Module.ToSoftObjectPath());
            }
        }
    }
    else if (!Setting->ModulesDataTable.IsNull())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to synchronously load ModulesDataTable: %s"), *Setting->ModulesDataTable.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("ModulesDataTable is not set in config."));
    }

    if (AssetsToLoad.IsEmpty())
    {
        UE_LOG(LogTemp, Log, TEXT("No modules to load. Calling OnAllModulesLoaded directly."));
        OnAllModulesLoaded();
        return;
    }
    
    //异步加载
    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
        AssetsToLoad,
        FStreamableDelegate::CreateUObject(this, &UDtModuleManagerSubsystem::OnAllModulesLoaded)
    );
}

TSubclassOf<ADtModuleBase> UDtModuleManagerSubsystem::GetModuleFromClass(TSubclassOf<ADtModuleBase> ModuleClass)
{
    for (auto& Module : M_Modules)
    {
        if (Module->GetClass() == ModuleClass)
        {
            return ModuleClass;
        }
        break;
    }
    return nullptr;
}

void UDtModuleManagerSubsystem::OnAllModulesLoaded()
{
    UE_LOG(LogTemp, Log, TEXT("所有模块加载完毕，系统准备就绪。"));
    
    const auto Setting = GetDefault<UDtModuleManagerConfig>();
    if (!Setting) return;

    
    auto temWorld = GetWorld();
    
    for (auto& CoreModulePtr : Setting->CoreModules)
    {
        if (TSubclassOf<UDtModuleToolBase> ModuleClass = CoreModulePtr.Get())
        {
            CoreModules.Add(temWorld->SpawnActor<UDtModuleToolBase>(ModuleClass));
            
            UE_LOG(LogTemp, Log, TEXT("CoreModule: %s 已加载"), *ModuleClass->GetName());
        }
    }
    
    if (UDataTable* LoadedTable = Setting->ModulesDataTable.Get())
    {
        static const FString ContextString(TEXT("Spawning M_Modules"));
        
        TArray<FName> RowNames = LoadedTable->GetRowNames();
        
        for (const FName& RowName : RowNames)
        {
            FModuleDataTable* RowData = LoadedTable->FindRow<FModuleDataTable>(RowName, ContextString);
            if (RowData && RowData->IsEnabled)
            {
                TSubclassOf<ADtModuleBase> ModuleClass = RowData->Module.Get();

                M_Modules.Add(temWorld->SpawnActor<ADtModuleBase>(ModuleClass));
                
                UE_LOG(LogTemp, Log, TEXT("Table Module: %s 已加载"), *ModuleClass->GetName());
            }
        }
    }
}

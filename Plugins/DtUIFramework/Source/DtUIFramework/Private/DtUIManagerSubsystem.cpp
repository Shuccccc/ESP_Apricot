// Fill out your copyright notice in the Description page of Project Settings.

#include "DtUIManagerSubsystem.h"
#include "DtRootViewport.h"
#include "Widget/UIFWidgetBase.h"
#include "DtRuntimeUIConfig.h"
#include "DtUIEventBroker.h"
#include "Engine/AssetManager.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

void UDtUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//	Collection.InitializeDependency<T>()
	
	Super::Initialize(Collection);

	OnWorldLoadedDelegateHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDtUIManagerSubsystem::OnWorldLoaded);
	
}

//--------------------------------[Subsystem初始化流程]--------------------------------
//再正式关卡加载后再初始化UI管理
void UDtUIManagerSubsystem::OnWorldLoaded(UWorld* NewWorld)
{
	//@TODO 后续转到BeginPlay模块

 	FString CurrentMapName = UGameplayStatics::GetCurrentLevelName(NewWorld);
	const FString StartupMapName = TEXT("M_Startup");

	if (!CurrentMapName.Equals(StartupMapName, ESearchCase::IgnoreCase))
	{
		UE_LOG(LogTemp, Log, TEXT("Main map '%s' detected! Starting Core UI initialization..."), *CurrentMapName);

		bIsCoreUIInitialized = true; // 标记，防止重复初始化

		InitBlueprintCache();
	}
}

//--------------------------------↓--------------------------------
//异步加载蓝图类 
void UDtUIManagerSubsystem::InitBlueprintCache()
{
	const auto Setting = GetDefault<UDtRuntimeUIConfig>();

	if (!Setting)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get settings!"));
		return ;
	}
	TArray<FSoftObjectPath> AssetsToLoad;

	if (!Setting->UMG_Window.IsNull())
	{
		AssetsToLoad.Add(Setting->UMG_Window.ToSoftObjectPath());
	}
	if (!Setting->UMG_WindowBar.IsNull())
	{
		AssetsToLoad.Add(Setting->UMG_WindowBar.ToSoftObjectPath());
	}
	
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(AssetsToLoad,FStreamableDelegate::CreateUObject(this, &UDtUIManagerSubsystem::OnBlueprintClassesLoaded));
}

//--------------------------------↓--------------------------------
//蓝图类加载完成回调 缓存蓝图类 添加根视口
void UDtUIManagerSubsystem::OnBlueprintClassesLoaded()
{
	const UDtRuntimeUIConfig* Setting = GetDefault<UDtRuntimeUIConfig>();
	if (!Setting)
	{
		return;
	}
	M_UMG_Window = Setting->UMG_Window.Get();
	M_UMG_WindowBar = Setting->UMG_WindowBar.Get();
	
//	UIM初始化流程转交至根视口
	
	if (M_RootViewport)
	{
		M_RootViewport->AddToViewport(8);
	}
	else
	{
		M_RootViewport = CreateWidget<UDtRootViewport>(GetWorld(), UDtRootViewport::StaticClass());
		M_RootViewport->AddToViewport(8);
	}
}

void UDtUIManagerSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(OnWorldLoadedDelegateHandle);
	Super::Deinitialize();
}

//--------------------------------[Subsystem初始化流程end]--------------------------------

/*void UDtUIManagerSubsystem::RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	if (InWidget.IsValid())
	{
		M_UIList.Add(InWidget);
	//	InWidget->TestPrint(TEXT("友元多态调用 :: "));
	}
}

void UDtUIManagerSubsystem::UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Remove(InWidget) ;
}*/

//--------------------------------[外部调用]--------------------------------

FDtUIStyle UDtUIManagerSubsystem::GetDefaultStyle()
{
	return M_DefaultStyle;
}

UUIFWidgetBase* UDtUIManagerSubsystem::GetWindow(FString ID)
{
	auto tem = CreateWidget<UUIFWidgetBase>(GetWorld(), M_UMG_Window);
	tem->AddToViewport(9);
	return tem ;
}

void UDtUIManagerSubsystem::SetTheme(FDtUIStyle Style)
{
	auto EventBroker = GetGameInstance()->GetSubsystem<UDtUIEventBroker>();
	M_CurrentStyle = Style;
	EventBroker->OnThemeChanged.Broadcast(Style);
}

FDtUIStyle UDtUIManagerSubsystem::GetUIStyle()
{
	return M_CurrentStyle ;
}




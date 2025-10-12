// Fill out your copyright notice in the Description page of Project Settings.

#include "DtUIManagerSubsystem.h"
#include "DtRootViewport.h"
#include "Widget/UIFWidgetBase.h"
#include "DtRuntimeUIConfig.h"
#include "Engine/AssetManager.h"
#include "Engine/Engine.h"

void UDtUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	OnWorldLoadedDelegateHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDtUIManagerSubsystem::OnWorldLoaded);

	InitBlueprintCache();
}

void UDtUIManagerSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(OnWorldLoadedDelegateHandle);
	Super::Deinitialize();
}

void UDtUIManagerSubsystem::RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
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
}

FDtUIStyle UDtUIManagerSubsystem::GetDefaultStyle()
{
	return M_DefaultStyle;
}

UUIFWidgetBase* UDtUIManagerSubsystem::GetWindow(FString ID)
{

	UUIFWidgetBase* CreatedWidget = CreateWidget<UUIFWidgetBase>(GetWorld(), M_UMG_Window);
    
	return CreatedWidget;
}

void UDtUIManagerSubsystem::SetTheme(FDtUIStyle Style)
{
	M_DefaultStyle = Style;
	
	auto temCDO = Cast<UUIFWidgetBase>(UUIFWidgetBase::StaticClass()->GetDefaultObject());
	temCDO->M_UIStyle=Style;
	
	for (auto i : M_UIList)
	{
		if (i.IsValid() && ! i->M_IsStylized)
		{
			i->SetTheme(Style);	
		}
	}
}

FDtUIStyle UDtUIManagerSubsystem::GetUIStyle()
{
	return M_DefaultStyle;
}

void UDtUIManagerSubsystem::OnWorldLoaded(UWorld* NewWorld)
{
	if (NewWorld && NewWorld->IsGameWorld())
	{
		M_World = NewWorld;
		
		if (M_RootViewport)
		{
			M_RootViewport->AddToViewport(8);
			return;
		}
		M_RootViewport = CreateWidget<UDtRootViewport>(NewWorld, UDtRootViewport::StaticClass());
		M_RootViewport->AddToViewport(8);
//		initRootPort();
	}
}

void UDtUIManagerSubsystem::initRootPort()
{
	M_World = GetWorld();
	
	/*UUIFWidgetBase* WindowBar = CreateWidget<UUIFWidgetBase>(M_World, M_UMG_WindowBar);
	
	M_RootViewport->AddToView(EDtUILayer::Window,WindowBar);*/
}

void UDtUIManagerSubsystem::InitBlueprintCache()
{
	const auto Setting = GetDefault<UDtRuntimeUIConfig>();

	if (!Setting)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get settings!"));
		return ;
	}
	TArray<FSoftObjectPath> AssetsToLoad;

	//加载窗口类
	if (!Setting->UMG_Window.IsNull())
	{
		AssetsToLoad.Add(Setting->UMG_Window.ToSoftObjectPath());
	}
	
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(AssetsToLoad,FStreamableDelegate::CreateUObject(this, &UDtUIManagerSubsystem::OnBlueprintClassesLoaded));
}

void UDtUIManagerSubsystem::OnBlueprintClassesLoaded()
{
	const UDtRuntimeUIConfig* Setting = GetDefault<UDtRuntimeUIConfig>();
	if (!Setting)
	{
		return;
	}
	M_UMG_Window = Setting->UMG_Window.Get();
	M_UMG_WindowBar = Setting->UMG_WindowBar.Get();
}

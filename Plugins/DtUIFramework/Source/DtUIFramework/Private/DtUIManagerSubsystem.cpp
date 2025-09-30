// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "DtRootViewport.h"
#include "UIFWidgetBase.h"

void UUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnWorldLoadedDelegateHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UUIManager::OnWorldLoaded);
}

void UUIManager::Deinitialize()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(OnWorldLoadedDelegateHandle);
	Super::Deinitialize();
}

void UUIManager::RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Add(InWidget);
	if (InWidget.IsValid())
	{
		InWidget->TestPrint(TEXT("友元多态调用 :: "));
	}
}

void UUIManager::UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Remove(InWidget) ;
}

void UUIManager::SetTheme(FDtUIStyle Style)
{
	M_DefaultStyle = Style;
	for (auto i : M_UIList)
	{
		if (i.IsValid() && ! i->M_IsStylized)
		{
			i->SetTheme(Style);	
		}
	}
}

void UUIManager::OnWorldLoaded(UWorld* NewWorld)
{
	if (NewWorld && NewWorld->IsGameWorld())
	{
		if (M_RootViewport)
		{
			M_RootViewport->AddToViewport(8);
		}
		M_RootViewport = CreateWidget<UDtRootViewport>(NewWorld, UDtRootViewport::StaticClass());
		M_RootViewport->AddToViewport(8);
	}
}

FDtUIStyle UUIManager::GetDefaultStyle()
{
	return M_DefaultStyle;
}

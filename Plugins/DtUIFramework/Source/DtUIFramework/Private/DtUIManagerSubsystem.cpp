// Fill out your copyright notice in the Description page of Project Settings.


#include "DtUIManagerSubsystem.h"
#include "DtRootViewport.h"
#include "UIFWidgetBase.h"

void UDtUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnWorldLoadedDelegateHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UDtUIManagerSubsystem::OnWorldLoaded);
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
		if (M_RootViewport)
		{
			M_RootViewport->AddToViewport(8);
		}
		M_RootViewport = CreateWidget<UDtRootViewport>(NewWorld, UDtRootViewport::StaticClass());
		M_RootViewport->AddToViewport(8);
	}
}

FDtUIStyle UDtUIManagerSubsystem::GetDefaultStyle()
{
	return M_DefaultStyle;
}

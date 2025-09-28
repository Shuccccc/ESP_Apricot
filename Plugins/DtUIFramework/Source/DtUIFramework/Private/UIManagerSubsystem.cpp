// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerSubsystem.h"
#include "DtRootViewport.h"
#include "UIFWidgetBase.h"

void UUIManagerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	M_RootViewport = CreateWidget<UDtRootViewport>(GetWorld(), UDtRootViewport::StaticClass());
	M_RootViewport->AddToViewport(8);
}

void UUIManagerSubsystem::RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Add(InWidget);
	if (InWidget.IsValid())
	{
		InWidget->TestPrint(TEXT("友元多态调用 :: "));
	}
}

void UUIManagerSubsystem::UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Remove(InWidget) ;
}

void UUIManagerSubsystem::SetTheme(FDtUIStyle Style)
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

FDtUIStyle UUIManagerSubsystem::GetDefaultStyle()
{
	return M_DefaultStyle;
}

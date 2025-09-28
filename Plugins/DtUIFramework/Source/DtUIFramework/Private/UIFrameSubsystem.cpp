// Fill out your copyright notice in the Description page of Project Settings.


#include "UIFrameSubsystem.h"
#include "DtRootViewport.h"
#include "UIFWidgetBase.h"
#include "Blueprint/UserWidget.h"

void UUIFrameSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	/*M_RootViewport = CreateWidget<UDtRootViewport>(GetWorld(), UDtRootViewport::StaticClass());
	M_RootViewport->AddToViewport(8);*/
}

void UUIFrameSubsystem::RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Add(InWidget);
	if (InWidget.IsValid())
	{
		InWidget->TestPrint(TEXT("友元多态调用 :: "));
	}
}

void UUIFrameSubsystem::UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget)
{
	M_UIList.Remove(InWidget) ;
}

FDtUIStyle UUIFrameSubsystem::GetDefaultStyle()
{
	return M_DefaultStyle;
}

void UUIFrameSubsystem::SetTheme(FDtUIStyle Style)
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

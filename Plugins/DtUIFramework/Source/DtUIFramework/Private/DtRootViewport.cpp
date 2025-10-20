// Fill out your copyright notice in the Description page of Project Settings.


#include "DtRootViewport.h"
#include "Blueprint/WidgetTree.h"
#include "Layer/UILayerBase.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widget/UIFWidgetWindowBase.h"
//Test
#include "Components/Button.h"
#include "Layer/UIWindowLayer.h"


bool UDtRootViewport::Initialize()
{
	auto bResult = Super::Initialize();

//婉拒CDO
	if(HasAnyFlags(RF_ClassDefaultObject))
	{
		return bResult;
	}

	//初始化控件树
	M_RootViewport = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), FName(TEXT("M_RootViewport")));
	WidgetTree->RootWidget = M_RootViewport;

	//TODO 狼狈 待修改  
	TArray<FName> LayerNames = {
		FName(TEXT("StaticLayer")),
		FName(TEXT("FloatingLayer")),
		FName(TEXT("WindowLayer")),
		FName(TEXT("NotificationLayer")),
		FName(TEXT("PopupLayer")),
		FName(TEXT("ProgressLayer")),
		FName(TEXT("SystemLayer")),
		FName(TEXT("TopLayer"))
	};
	TMap<FName, UUILayerBase*> LayerMap;
	for (const FName& LayerName : LayerNames)
	{
		UUILayerBase* NewLayer = nullptr;
		if (LayerName == TEXT("WindowLayer"))
		{
			NewLayer = CreateWidget<UUIWindowLayer>(this, UUIWindowLayer::StaticClass(), LayerName);
		}
		else
		{
			NewLayer = CreateWidget<UUILayerBase>(this, UUILayerBase::StaticClass(), LayerName);
		}
		if (NewLayer)
		{
			NewLayer->SetAnchorPoint(); 
			M_RootViewport->AddChildToCanvas(NewLayer);
			LayerMap.Add(LayerName, NewLayer); 
		}
	}

	M_StaticLayer = LayerMap.FindRef(TEXT("StaticLayer"));
	M_FloatingLayer = LayerMap.FindRef(TEXT("FloatingLayer"));
	
	M_WindowLayer = Cast<UUIWindowLayer>(LayerMap.FindRef(TEXT("WindowLayer"))); 
    
	M_NotificationLayer = LayerMap.FindRef(TEXT("NotificationLayer"));
	M_PopupLayer = LayerMap.FindRef(TEXT("PopupLayer"));
	M_ProgressLayer = LayerMap.FindRef(TEXT("ProgressLayer"));
	M_SystemLayer = LayerMap.FindRef(TEXT("SystemLayer"));
	M_TopLayer = LayerMap.FindRef(TEXT("TopLayer"));
	
// 这里是添加一个测试按钮
	if (GIsEditor)
	{
		UButton* NewButton = WidgetTree->ConstructWidget<UButton>();
		NewButton->SetBackgroundColor(FLinearColor::Red);
    
		UCanvasPanelSlot* ButtonSlot = M_StaticLayer->M_MainPanel->AddChildToCanvas(NewButton);
		ButtonSlot->SetPosition(FVector2D(100, 200));
		ButtonSlot->SetSize(FVector2D(150, 50));
	}
	
	return bResult;
}

UUIFWidgetWindowBase* UDtRootViewport::GetWindow(FString ID)
{
	return M_WindowLayer->CreateWindow(ID);
}

void UDtRootViewport::AddToView(EDtUILayer Layer , UUserWidget* Widget )
{
	switch (Layer)
	{
	case EDtUILayer::Static:
		M_StaticLayer->AddWidgetToCanvas(Widget);
		break;
		
	case EDtUILayer::Floating:
		M_FloatingLayer->AddWidgetToCanvas(Widget);
		break;

	case EDtUILayer::Window:
		M_WindowLayer->AddWidgetToCanvas(Widget);
		break;
		
	case EDtUILayer::Notification:
		M_NotificationLayer->AddWidgetToCanvas(Widget);
		break;
		
	case EDtUILayer::Popup:
		M_PopupLayer->AddWidgetToCanvas(Widget);
		break;
		
	case EDtUILayer::Progress:
		M_ProgressLayer->AddWidgetToCanvas(Widget);
		break;
		
	case EDtUILayer::System:
		M_SystemLayer->AddWidgetToCanvas(Widget);
		break;
	case EDtUILayer::Top:
		M_TopLayer->AddWidgetToCanvas(Widget);
		break;
	}
}

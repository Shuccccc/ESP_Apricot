// Fill out your copyright notice in the Description page of Project Settings.


#include "Layer/UIWindowLayer.h"
#include "Components/CanvasPanel.h"
#include "Widget/UIFWidgetBase.h"
#include "Components/CanvasPanelSlot.h"
#include "DtUIManagerSubsystem.h"

bool UUIWindowLayer::Initialize()
{
	return Super::Initialize();
}

void UUIWindowLayer::NativeConstruct()
{
	Super::NativeConstruct();
	
	M_UIManager = GetGameInstance()->GetSubsystem<UDtUIManagerSubsystem>();

	M_WindowClass = M_UIManager->M_UMG_Window;
	M_WindowBarClass = M_UIManager->M_UMG_WindowBar;

	M_WindowBar = CreateWidget<UUIFWidgetBase>(this, M_WindowBarClass);

	M_RootViewport->AddChild(M_WindowBar);

	auto temPanel = Cast<UCanvasPanelSlot>(M_WindowBar->Slot);
	if (temPanel)
	{
		temPanel->SetZOrder(50);
		temPanel->SetPosition(FVector2D(24,128));
		temPanel->SetSize(FVector2D(22,40));
	}
}

int UUIWindowLayer::GetChildrenCount()
{
	return M_RootViewport->GetChildrenCount();
}

void UUIWindowLayer::SetTopZOrder(UUIFWidgetBase* Widget)
{
	auto Children = M_RootViewport->GetAllChildren();

	for (auto Child : Children)
	{
		//过滤掉窗口栏 并保持窗口栏置顶
		if (Child->StaticClass() != M_WindowClass)
		{
			Cast<UCanvasPanelSlot>(Child->Slot)->SetZOrder( M_RootViewport->GetChildrenCount()+1);
			continue;
		}
		//先把在选中窗口之上的窗口ZOrder减一 腾出最高位 
		if (Child != Widget)
		{
			auto TemSlot = Cast<UCanvasPanelSlot>(Child->Slot);
			if (TemSlot->GetZOrder() >= M_RootViewport->GetChildrenCount())
			{
				TemSlot->SetZOrder(TemSlot->GetZOrder()-1);
			}
		}
		else
		{
			//最后把选中窗口置顶
			auto TemSlot = Cast<UCanvasPanelSlot>(Child->Slot);
			TemSlot->SetZOrder(M_RootViewport->GetChildrenCount());
		}
	}
}

void UUIWindowLayer::SetTopZOrderFromAI(UUIFWidgetBase* WidgetToSetTop)
{
	const int32 NumWindows = M_RootViewport->GetChildrenCount() - 1;
	const int32 TopZOrder = NumWindows - 1;

	UCanvasPanelSlot* TargetSlot = Cast<UCanvasPanelSlot>(WidgetToSetTop->Slot);
	const int32 WidgetCurrentZ = TargetSlot->GetZOrder();

	// 如果它已经是顶层了，就什么都不用做
	if (WidgetCurrentZ == TopZOrder)
	{
		return;
	}

	// 遍历所有子控件，找到那些在当前窗口之上的窗口，把它们的ZOrder减一
	for (UWidget* Child : M_RootViewport->GetAllChildren())
	{
		// 跳过目标窗口本身和非窗口控件（窗口栏）
		if (Child == WidgetToSetTop || !Child->IsA(M_WindowClass))
		{
			continue;
		}

		UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(Child->Slot);
		// 如果这个窗口在目标窗口的上方，就把它“往下拉一层”
		if (ChildSlot->GetZOrder() > WidgetCurrentZ)
		{
			ChildSlot->SetZOrder(ChildSlot->GetZOrder() - 1);
		}
	}

	// 最后，把目标窗口设置到最顶层
	TargetSlot->SetZOrder(TopZOrder);
}

void UUIWindowLayer::AddWindowToCanvas(UUIFWidgetBase* Widget) const
{
	M_RootViewport->AddChild(Widget);
	Cast<UCanvasPanelSlot>(Widget->Slot)->SetZOrder(M_RootViewport->GetChildrenCount());
}

void UUIWindowLayer::CreateWindow()
{
	
	
}


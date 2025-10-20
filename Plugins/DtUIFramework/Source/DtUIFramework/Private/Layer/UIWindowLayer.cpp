// Fill out your copyright notice in the Description page of Project Settings.


#include "Layer/UIWindowLayer.h"
#include "Components/CanvasPanel.h"
#include "Widget/UIFWidgetWindowBase.h"
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

	M_MainPanel->AddChild(M_WindowBar.Get());

	auto temPanel = Cast<UCanvasPanelSlot>(M_WindowBar->Slot);
	if (temPanel)
	{
		temPanel->SetZOrder(50);
		temPanel->SetPosition(FVector2D(24,128));
		temPanel->SetSize(FVector2D(22,40));
		temPanel->SetAutoSize(true);
	}
}

int UUIWindowLayer::GetChildrenCount()
{
	return M_MainPanel->GetChildrenCount();
}

void UUIWindowLayer::SetTopZOrder(UUIFWidgetBase* Widget)
{
	auto Children = M_MainPanel->GetAllChildren();

	for (auto Child : Children)
	{
		//过滤掉窗口栏 并保持窗口栏置顶
		if (Child->StaticClass() != M_WindowClass)
		{
			Cast<UCanvasPanelSlot>(Child->Slot)->SetZOrder( M_MainPanel->GetChildrenCount()+1);
			continue;
		}
		//先把在选中窗口之上的窗口ZOrder减一 腾出最高位 
		if (Child != Widget)
		{
			auto TemSlot = Cast<UCanvasPanelSlot>(Child->Slot);
			if (TemSlot->GetZOrder() >= M_MainPanel->GetChildrenCount())
			{
				TemSlot->SetZOrder(TemSlot->GetZOrder()-1);
			}
		}
		else
		{
			//最后把选中窗口置顶
			auto TemSlot = Cast<UCanvasPanelSlot>(Child->Slot);
			TemSlot->SetZOrder(M_MainPanel->GetChildrenCount());
		}
	}
}

void UUIWindowLayer::SetTopZOrderFromAI(UUIFWidgetBase* WidgetToSetTop)
{
	const int32 NumWindows = M_MainPanel->GetChildrenCount() - 1;
	const int32 TopZOrder = NumWindows - 1;

	UCanvasPanelSlot* TargetSlot = Cast<UCanvasPanelSlot>(WidgetToSetTop->Slot);
	const int32 WidgetCurrentZ = TargetSlot->GetZOrder();

	// 如果它已经是顶层了，就什么都不用做
	if (WidgetCurrentZ == TopZOrder)
	{
		return;
	}

	// 遍历所有子控件，找到那些在当前窗口之上的窗口，把它们的ZOrder减一
	for (UWidget* Child : M_MainPanel->GetAllChildren())
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
	M_MainPanel->AddChild(Widget);
	Cast<UCanvasPanelSlot>(Widget->Slot)->SetZOrder(M_MainPanel->GetChildrenCount());
}

UUIFWidgetWindowBase* UUIWindowLayer::CreateWindow(FString ID )
{
	UUIFWidgetWindowBase* temWindow;
	
	if (Windows.Contains(ID) )
	{
		if (Windows.FindRef(ID).IsValid())
		{
			temWindow = Windows.FindRef(ID).Get();
			temWindow->WindowActionRequested(EDtWindowAction::Restore);
			
			return temWindow;
		}
		else
		{
			Windows.Remove(ID);
		}
	}
	
	temWindow = CreateWidget<UUIFWidgetWindowBase>(this , M_WindowClass);
	temWindow->PrivateID = ID;
	
	Windows.Add(ID , temWindow);

	M_MainPanel->AddChild(temWindow);

	return temWindow;
}

void UUIWindowLayer::Internal_MoveWindowToFront()
{
	
	
}

void UUIWindowLayer::RemoveWindow(FString ID)
{
	Windows.Remove(ID);
}


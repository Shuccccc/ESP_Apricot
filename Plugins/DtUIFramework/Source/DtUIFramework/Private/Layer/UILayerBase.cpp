// Fill out your copyright notice in the Description page of Project Settings.


#include "Layer/UILayerBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UUILayerBase::AddWidgetToCanvas(UUserWidget* Widget) const
{
	M_MainPanel->AddChild(Widget);
}

bool UUILayerBase::Initialize()
{
	bool bResult = Super::Initialize();
	if(HasAnyFlags(RF_ClassDefaultObject))
	{
		return bResult;
	}
	
	M_MainPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(),FName(TEXT("RootViewport")));

	WidgetTree->RootWidget = M_MainPanel;
	return bResult ;

}

void UUILayerBase::SetAnchorPoint()
{
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot);
	
	if (CanvasSlot)
	{
		CanvasSlot->SetAnchors(FAnchors{0,0,1,1});
		CanvasSlot->SetOffsets(0);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWindowBar.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/InvalidationBox.h"
#include "Components/Overlay.h"
#include "Components/ScrollBox.h"

bool UTestWindowBar::Initialize()
{
	bool bResult = Super::Initialize();

	if(HasAnyFlags(RF_ClassDefaultObject))
	{
		return bResult;
	}
	M_RootPanel = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), FName(TEXT("RootPanel")));
	WidgetTree->RootWidget =M_RootPanel;

	//初始化内部组件
	M_BG_Left = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), FName(TEXT("LeftBGC")));
	M_BG_Mind = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), FName(TEXT("MindBGC")));
	M_BG_Right = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), FName(TEXT("RightBGC")));

	M_BD_InvalidBox = WidgetTree->ConstructWidget<UInvalidationBox>(UInvalidationBox::StaticClass(), FName(TEXT("InvalidBox")));
	M_FN_DragButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), FName(TEXT("DragButton")));
	M_CT_ScrollBox = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), FName(TEXT("ScrollBox")));

	//初始化控件树
	
	
	/*
	UTexture2D* LeftBGTex = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/DtUIFramework/Resource/Window/Component/WindowBar_scrol_Left.WindowBar_scrol_Left")));
	M_BG_Left->SetBrushFromTexture(LeftBGTex);
	UOverlaySlot * LeftSlot = M_RootPanel->AddChildToOverlay(M_BG_Left);
	*/

	return bResult;

}

void UTestWindowBar::LodAsset()
{
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidgetcomponent.h"
#include "SlateAssetConfig.hpp"
#include "Components/InvalidationBox.h"
#include "Widgets/SInvalidationPanel.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Images/SImage.h"

void STestWidgetComponent::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(M_RootPanel , SOverlay)
	//左边框
		+ SOverlay::Slot()
		.Padding(0)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Fill )
		[
			SAssignNew(M_BG_Left,SImage)
			.Image(FCoreStyle::Get().GetDefaultBrush())
			.DesiredSizeOverride(FVector2D{2,38})
		]
	//中间框
		+ SOverlay::Slot().Padding(2,0,2,0)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(M_BG_Mind,SImage)
			.Image(FCoreStyle::Get().GetDefaultBrush())
		]
	//右边框
		+ SOverlay::Slot().Padding(0)
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(M_BG_Right,SImage)
			.Image(FCoreStyle::Get().GetDefaultBrush())
			.DesiredSizeOverride(FVector2D{2,38})
			.RenderTransform(FSlateRenderTransform(FScale2D(-1.0f, 1.0f)))
			.RenderTransformPivot(FVector2D(0.5f, 0.5f))
		]
		+SOverlay::Slot()
		.Padding(4,0,0,0)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SAssignNew(M_FN_DragButton , SButton)
		]
		+SOverlay::Slot()
		.Padding(14,4,4,4)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(M_CT_ScrollBox , SScrollBox)
			.ScrollBarVisibility(EVisibility::Collapsed)
			.ConsumeMouseWheel(EConsumeMouseWheel::Always)
		]
	];
}

void STestWidgetComponent::LoadAsset()
{
	
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SI_BG_Left));
	if (Texture)
	{
		FSlateBrush* LeftBrush = new FSlateBrush();
		LeftBrush->SetResourceObject(Texture);
		M_BG_Left->SetImage(LeftBrush);

		FSlateBrush* RightBrush = new FSlateBrush();
		RightBrush->SetResourceObject(Texture);
		M_BG_Right->SetImage(RightBrush);
	}
	M_BG_Mind->SetImage(new FSlateNoResource());
	M_BG_Mind->SetColorAndOpacity(FLinearColor::White);
	
}

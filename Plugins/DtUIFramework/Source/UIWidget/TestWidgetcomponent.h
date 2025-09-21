// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SOverlay;
class SImage;
class SInvalidationPanel;
class SButton;
class SScrollBox;

class UIWIDGET_API STestWidgetComponent : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STestWidgetComponent)
	{
		
	}
	SLATE_END_ARGS()

	void LoadAsset ();
	void Construct(const FArguments& InArgs);
private:
	
	// 添加Construct函数


	TSharedPtr<SOverlay> M_RootPanel;

	TSharedPtr<SImage> M_BG_Left;

	TSharedPtr<SImage> M_BG_Mind;

	TSharedPtr<SImage> M_BG_Right;

	TSharedPtr<SInvalidationPanel> M_BD_InvalidBox;

	TSharedPtr<SButton> M_FN_DragButton;

	TSharedPtr<SScrollBox> M_CT_ScrollBox;
	
};

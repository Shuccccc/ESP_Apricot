// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCustomWidget.h"

#include "TestWidgetcomponent.h"

UTestCustomWidget::UTestCustomWidget()
{
	// 设置默认值
	DesiredSize = FVector2D(20.0f, 128.0f);
	HorizontalAlignment = HAlign_Left;
	VerticalAlignment = VAlign_Fill;
	
}

TSharedRef<SWidget> UTestCustomWidget::RebuildWidget()
{
	{
		// 创建Slate控件
		MyTestWidgetComponent = SNew(STestWidgetComponent);
	
		// 使用SBox包装控件以支持对齐和尺寸设置
		TSharedRef<SBox> Box = SNew(SBox)
			[
				MyTestWidgetComponent.ToSharedRef()
			];
	
		return Box;
	}
}

void UTestCustomWidget::SynchronizeProperties()
{
	// 同步属性到Slate控件
	Super::SynchronizeProperties();

	if (MyTestWidgetComponent.IsValid())
	{
		// 在这里同步任何需要的属性
		MyTestWidgetComponent->LoadAsset();
	}
}

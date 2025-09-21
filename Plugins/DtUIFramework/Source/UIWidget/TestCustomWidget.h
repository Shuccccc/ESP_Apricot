// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "TestCustomWidget.generated.h"

class STestWidgetComponent;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleasedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHoverEvent);



UCLASS()
class UIWIDGET_API UTestCustomWidget : public UWidget
{
	GENERATED_BODY()
public:
	UTestCustomWidget();

	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

protected:
	// 在蓝图中可编辑的属性示例
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestWidgetComponent")
	FVector2D DesiredSize;

	// 控件对齐属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestWidgetComponent|Alignment")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestWidgetComponent|Alignment")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment;

private:
	// Slate控件的共享指针
	TSharedPtr<STestWidgetComponent> MyTestWidgetComponent;
};

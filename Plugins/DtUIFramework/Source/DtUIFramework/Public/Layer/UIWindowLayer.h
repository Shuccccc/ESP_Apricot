// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILayerBase.h"
#include "UIWindowLayer.generated.h"

class UDtUIManagerSubsystem;
class UUIFWidgetBase;
/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIWindowLayer : public UUILayerBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	int GetChildrenCount();

	void SetTopZOrder(UUIFWidgetBase* Widget);

	void SetTopZOrderFromAI(UUIFWidgetBase* WidgetToSetTop);

	void AddWindowToCanvas(UUIFWidgetBase* Widget) const;

private:

	TSubclassOf<UUIFWidgetBase> M_WindowClass;
	UPROPERTY()
	UDtUIManagerSubsystem* M_UIManager;
};

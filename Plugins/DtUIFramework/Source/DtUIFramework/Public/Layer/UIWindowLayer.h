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

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
	int GetChildrenCount();

	void SetTopZOrder(UUIFWidgetBase* Widget);

	void SetTopZOrderFromAI(UUIFWidgetBase* WidgetToSetTop);

	void AddWindowToCanvas(UUIFWidgetBase* Widget) const;

	void CreateWindow ();

private:
	
	UPROPERTY()
	UUIFWidgetBase* M_WindowBar;

	UPROPERTY()
	TMap<FString,UUIFWidgetBase*> Windows;
	
	TSubclassOf<UUIFWidgetBase> M_WindowClass;

	TSubclassOf<UUIFWidgetBase> M_WindowBarClass;

	
	UPROPERTY()
	UDtUIManagerSubsystem* M_UIManager;
};

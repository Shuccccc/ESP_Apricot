// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UILayerBase.h"
#include "UIWindowLayer.generated.h"

class UDtUIManagerSubsystem;
class UUIFWidgetBase;
class UUIFWidgetWindowBase;
/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIWindowLayer : public UUILayerBase
{
	GENERATED_BODY()

	friend class UUIFWidgetWindowBase ;
public:

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
	int GetChildrenCount();

	void SetTopZOrder(UUIFWidgetBase* Widget);

	void SetTopZOrderFromAI(UUIFWidgetBase* WidgetToSetTop);

	void AddWindowToCanvas(UUIFWidgetBase* Widget) const;

	UUIFWidgetWindowBase* CreateWindow (FString ID );


private:

	void Internal_MoveWindowToFront();
	
	void RemoveWindow(FString ID);
	
	UPROPERTY()
	TWeakObjectPtr<UUIFWidgetBase> M_WindowBar;

	UPROPERTY()
	TMap<FString,TWeakObjectPtr<UUIFWidgetWindowBase>> Windows;
	
	TSubclassOf<UUIFWidgetWindowBase> M_WindowClass;

	TSubclassOf<UUIFWidgetBase> M_WindowBarClass;
	
	UPROPERTY()
	UDtUIManagerSubsystem* M_UIManager;
};

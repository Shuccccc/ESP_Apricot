// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/UIFWidgetBase.h"
#include "UIFWidgetWindowBase.generated.h"

/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIFWidgetWindowBase : public UUIFWidgetBase
{
	GENERATED_BODY()

	friend class UUIWindowLayer ;

private:

	FString PrivateID;

protected:

	//绑定至动画完成时的属性重置
	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenWindowComplete();
	
	//绑定至动画完成时的属性重置
	UFUNCTION(BlueprintImplementableEvent)
	void OnMinimizeComplete();
	
	//绑定至动画完成时的属性重置
	UFUNCTION(BlueprintImplementableEvent)
	void OnRestoreComplete();
	
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void WindowActionRequested(EDtWindowAction Action);

	UFUNCTION(BlueprintCallable)
	void OnWindowActionReceived(UUIFWidgetBase* TargetWindow, EDtWindowAction Action);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void CloseWindowBeginNative();

private:
	
	UPROPERTY()
	TWeakObjectPtr<UUIWindowLayer> OwningLayerPtr;
};

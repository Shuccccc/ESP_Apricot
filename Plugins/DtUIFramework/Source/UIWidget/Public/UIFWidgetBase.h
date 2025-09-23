// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DtUIFStruct.h"
#include "UIFWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UIWIDGET_API UUIFWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

//	void Initialize() override;
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "UIStyle"))
	FDtUIStyle GetUIStyle();
	
	UFUNCTION(BlueprintCallable)
	void SetUIStyle(FDtUIStyle NewStyle);
	
		
	//用于初始化以及刷新样式
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStyle();

private:

	UPROPERTY(BlueprintGetter="GetUIStyle", BlueprintSetter="SetUIStyle")
	FDtUIStyle M_UIStyle;

	friend class UUIManagerSubsystem;
	

	void LerpColor();

	FTimerHandle M_TimerHandle;

	float M_LerpAlpha;
	
	FDtUIStyle M_NewColor;
	

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DtUIFStruct.h"
#include "UIFWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UIWIDGET_API UUIFWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
	friend class UUIManagerSubsystem;
	
public:
	
	void NativeConstruct() override;

	void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "UIStyle"))
	FDtUIStyle GetUIStyle();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "UIStyle"))
	bool GetStylized();
	
	UFUNCTION(BlueprintCallable)
	void SetStylized(bool IsStylized);
		
	//用于初始化以及刷新样式
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStyle();

private:
	
	void SetUIStyle(FDtUIStyle NewStyle);
	
	UPROPERTY(BlueprintGetter="GetUIStyle" )//BlueprintSetter="SetUIStyle"
	FDtUIStyle M_UIStyle;

	UPROPERTY(BlueprintGetter="GetStylized", BlueprintSetter="SetStylized")
	bool M_IsStylized;

	void TestPrint ( FString Tem);
	
	void LerpColor();

	FTimerHandle M_TimerHandle;

	float M_LerpAlpha;
	
	FDtUIStyle M_NewColor;

};

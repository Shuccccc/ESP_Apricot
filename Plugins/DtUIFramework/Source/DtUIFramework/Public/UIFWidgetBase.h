// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DtUIFStruct.h"
#include "UIManagerSubsystem.h"
#include "UIFWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DTUIFRAMEWORK_API UUIFWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
	friend class UUIManagerSubsystem;
	
public:
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "UIStyle"))
	FDtUIStyle GetUIStyle();

	UFUNCTION(BlueprintCallable , meta=(CompactNodeTitle = "UIStyle"))
	void ResetUIStyle();

	/*UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "UIStyle"))
	bool GetStylized();

	UFUNCTION(BlueprintCallable)
	void SetStylized(bool IsStylized);*/

	//用于初始化以及刷新样式
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStyle();

protected:
	
	UFUNCTION(BlueprintCallable,Category="Default")
	void SetTheme(FDtUIStyle NewStyle , bool IsStylized = false);
	
private:
	
	UPROPERTY(Blueprintable,BlueprintGetter="GetUIStyle")//BlueprintSetter="SetUIStyle"
	FDtUIStyle M_UIStyle;

	bool M_IsStylized;

	void TestPrint ( FString Tem);
	
	void LerpColor();

	FTimerHandle M_TimerHandle;

	float M_LerpAlpha;
	
	FDtUIStyle M_NewColor;

//	friend FDtUIStyle UUIManagerSubsystem::GetDefaultStyle();
};

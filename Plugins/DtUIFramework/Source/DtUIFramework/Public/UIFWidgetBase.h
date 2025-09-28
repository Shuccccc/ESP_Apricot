// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DtUIFStruct.h"
//#include "UIManagerSubsystem.h"
#include "UIFWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DTUIFRAMEWORK_API UUIFWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
	friend class UUIManagerSubsystem;

	friend class UUIFrameSubsystem;
	
public:
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(CompactNodeTitle = "UIStyle"))
	FDtUIStyle GetUIStyle();

	UFUNCTION(BlueprintCallable , meta=(CompactNodeTitle = "UIStyle"))
	void ResetUIStyle();

	//用于初始化以及刷新样式
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStyle();

protected:

	/**
	 * @param	NewStyle	新主题
	 * @param	IsStylized	是否作为独立样式 true: 主题更新时将忽略该控件 false: 在下一次主题更新时会新主题被覆盖
	 */
	UFUNCTION(BlueprintCallable,Category="Default")
	void SetTheme(FDtUIStyle NewStyle , bool IsStylized = false);
	
private:
	
	UPROPERTY(Blueprintable,BlueprintGetter="GetUIStyle")//BlueprintSetter="SetUIStyle"
	FDtUIStyle M_UIStyle;

	bool M_IsStylized =  false;

	void TestPrint ( FString Tem);
	
	void LerpColor();

	FTimerHandle M_TimerHandle;

	float M_LerpAlpha;
	
	FDtUIStyle M_NewColor;

//	friend FDtUIStyle UUIManagerSubsystem::GetDefaultStyle();
};

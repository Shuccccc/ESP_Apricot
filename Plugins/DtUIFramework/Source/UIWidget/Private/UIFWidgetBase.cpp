// Fill out your copyright notice in the Description page of Project Settings.


#include "UIFWidgetBase.h"

FDtUIStyle UUIFWidgetBase::GetUIStyle()
{
	return M_UIStyle;
}

void UUIFWidgetBase::SetUIStyle(FDtUIStyle NewStyle)
{
	M_NewColor = NewStyle;

	// 启动插值定时器
	if (!GetWorld()->GetTimerManager().IsTimerActive(M_TimerHandle))
	{
		M_LerpAlpha = 0.f;
		GetWorld()->GetTimerManager().SetTimer(M_TimerHandle, this, &UUIFWidgetBase::LerpColor, 0.0333f, true);
	}
}


void UUIFWidgetBase::LerpColor()
{
	M_LerpAlpha+=0.0333f;
	if (M_LerpAlpha >=1.f)
	{
		M_UIStyle = M_NewColor;
		UpdateStyle();
		GetWorld()->GetTimerManager().ClearTimer(M_TimerHandle);
	}
	M_UIStyle.AccentColor = FLinearColor::LerpUsingHSV(M_UIStyle.AccentColor,M_NewColor.AccentColor,M_LerpAlpha);
	M_UIStyle.ComponentColor = FLinearColor::LerpUsingHSV(M_UIStyle.ComponentColor,M_NewColor.ComponentColor,M_LerpAlpha);
	M_UIStyle.ComponentSecondaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.ComponentSecondaryColor,M_NewColor.ComponentSecondaryColor,M_LerpAlpha);
	M_UIStyle.PrimaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.PrimaryColor,M_NewColor.PrimaryColor,M_LerpAlpha);
	M_UIStyle.SecondaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.SecondaryColor,M_NewColor.SecondaryColor,M_LerpAlpha);
	M_UIStyle.TertiaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.TertiaryColor,M_NewColor.TertiaryColor,M_LerpAlpha);
	/*FLinearColor::LerpUsingHSV(M_UIStyle.ComponentColor,M_NewColor.ComponentColor,M_LerpAlpha);
	FLinearColor::LerpUsingHSV(M_UIStyle.ComponentSecondaryColor,M_NewColor.ComponentSecondaryColor,M_LerpAlpha);
	FLinearColor::LerpUsingHSV(M_UIStyle.PrimaryColor,M_NewColor.PrimaryColor,M_LerpAlpha);
	FLinearColor::LerpUsingHSV(M_UIStyle.SecondaryColor,M_NewColor.SecondaryColor,M_LerpAlpha);
	FLinearColor::LerpUsingHSV(M_UIStyle.TertiaryColor,M_NewColor.TertiaryColor,M_LerpAlpha);*/
	
	UpdateStyle();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UIFWidgetBase.h"

#include "DtUIEventBroker.h"
#include "DtUIManagerSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

void UUIFWidgetBase::SetUIStyle(FDtUIStyle NewStyle)
{
	M_UIStyle = NewStyle;
}

void UUIFWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	Guid = FGuid::NewGuid();
	
	// 不再向UIM注册 用事件分发解耦
	auto UIManager = GetGameInstance()->GetSubsystem<UDtUIManagerSubsystem>();
	UIManager->RegisterUI(this);

	//未实现
	auto EventBroker = GetGameInstance()->GetSubsystem<UDtUIEventBroker>();
	EventBroker->OnThemeChanged.AddDynamic(this,&UUIFWidgetBase::HandleThemeChanged);
}

void UUIFWidgetBase::NativeDestruct()
{
	auto UIManager = GetGameInstance()->GetSubsystem<UDtUIManagerSubsystem>();

	UIManager->UnRegisterUI(this);
	
//	FString LogTem = this->GetDisplayNameBase().ToString();
//	UKismetSystemLibrary::PrintString(this, LogTem+TEXT("  已注销"), true,true, FColor::Red, 8.0f);

	Super::NativeDestruct();
}

FDtUIStyle UUIFWidgetBase::GetUIStyle()
{
	return M_UIStyle;
}
void UUIFWidgetBase::ResetUIStyle()
{
	auto UIManager = GetGameInstance()->GetSubsystem<UDtUIManagerSubsystem>();
	SetTheme(UIManager->GetDefaultStyle(),true);
}


void UUIFWidgetBase::HandleThemeChanged(FDtUIStyle NewStyle)
{
	
}


void UUIFWidgetBase::SetTheme(FDtUIStyle NewStyle , bool IsStylized)
{
	M_NewColor = NewStyle;
	M_IsStylized = IsStylized;
	// 启动插值定时器
	if (!GetWorld()->GetTimerManager().IsTimerActive(M_TimerHandle))
	{
		M_LerpAlpha = 0.f;
		GetWorld()->GetTimerManager().SetTimer(M_TimerHandle, this, &UUIFWidgetBase::LerpColor, 0.0333f, true);
	}
}


void UUIFWidgetBase::TestPrint(FString Tem)
{

	FString LogTem = Tem ;

	UKismetSystemLibrary::PrintString(this, LogTem, true,true, FColor::Red, 8.0f);
	
}

void UUIFWidgetBase::LerpColor()
{
	M_LerpAlpha+=0.0666f;
	if (M_LerpAlpha >=1.f)
	{
		M_UIStyle = M_NewColor;
		UpdateStyle();
		GetWorld()->GetTimerManager().ClearTimer(M_TimerHandle);
		return;
	}
	
	M_UIStyle.AccentColor = FLinearColor::LerpUsingHSV(M_UIStyle.AccentColor,M_NewColor.AccentColor,M_LerpAlpha);
	M_UIStyle.PrimaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.PrimaryColor,M_NewColor.PrimaryColor,M_LerpAlpha);
	M_UIStyle.TertiaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.TertiaryColor,M_NewColor.TertiaryColor,M_LerpAlpha);
	M_UIStyle.SecondaryColor = FLinearColor::LerpUsingHSV(M_UIStyle.SecondaryColor,M_NewColor.SecondaryColor,M_LerpAlpha);
	
	UpdateStyle();
}

/*bool UUIFWidgetBase::GetStylized()
{
	return M_IsStylized;
}
void UUIFWidgetBase::SetStylized(bool IsStylized)
{
	M_IsStylized = IsStylized;
}*/
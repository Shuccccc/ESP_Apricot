// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtUIFStruct.h"
#include "DtUIEventBroker.generated.h"


class UUIFWidgetBase;

//---------------------------Cpp-------------------------------

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThemeChanged, FDtUIStyle, NewStyle);

//---------------------------Window----------------------------
UENUM(BlueprintType)
enum class EDtWindowAction : uint8
{
	Restore,
	Minimize,
	Close,
	Focus
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWindowCreated, UUIFWidgetBase*, CreatedWindow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWindowDestroyed, UUIFWidgetBase*, DestroyedWindow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWindowStateChanged, UUIFWidgetBase*, TargetWindow, EDtWindowAction, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWindowActionRequested, UUIFWidgetBase*, TargetWindow, EDtWindowAction, Action);


UCLASS()
class DTUIFRAMEWORK_API UDtUIEventBroker :  public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
//-------------------C++内部使用的Delegate----------------------------

	FOnThemeChanged OnThemeChanged;
	
//-------------------供蓝图使用的Delegate----------------------------


	//---------------------------Window----------------------------
	UPROPERTY(BlueprintAssignable, Category = "UI Events | Window")
	FOnWindowCreated OnWindowCreated;
	
	UPROPERTY(BlueprintAssignable, Category = "UI Events | Window")
	FOnWindowDestroyed OnWindowDestroyed;
	
	UPROPERTY(BlueprintAssignable, Category = "UI Events | Window")
	FOnWindowStateChanged OnWindowStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "UI Events | Window")
	FOnWindowActionRequested OnWindowActionRequested;
	
	//---------------------------WindowFunction--------------------
	
	UFUNCTION(BlueprintCallable , Category = "UI Broadcast | Window")
	void WindowCreatedBroadcast(UUIFWidgetBase* CreatedWindow);

	UFUNCTION(BlueprintCallable , Category = "UI Broadcast | Window")
	void WindowDestroyedBroadcast(UUIFWidgetBase* CreatedWindow);
	
	UFUNCTION(BlueprintCallable , Category = "UI Broadcast | Window")
	void WindowStateChangedBroadcast(UUIFWidgetBase* CreatedWindow , EDtWindowAction Action);

	UFUNCTION(BlueprintCallable , Category = "UI Broadcast | Window")
	void WindowActionRequestedBroadcast (UUIFWidgetBase* CreatedWindow , EDtWindowAction Action);
};

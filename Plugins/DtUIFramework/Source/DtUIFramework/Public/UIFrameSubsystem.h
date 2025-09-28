// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DtUIFStruct.h"
#include "Subsystems/WorldSubsystem.h"
#include "UIFrameSubsystem.generated.h"


class UDtRootViewport;
class UUIFWidgetBase;

/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIFrameSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	//注册UI
	void RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget);

	void UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget);

	FDtUIStyle GetDefaultStyle();

	UFUNCTION(BlueprintCallable)
	void SetTheme(FDtUIStyle Style);
	
	UPROPERTY()
	TObjectPtr<UDtRootViewport> M_RootViewport;

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<UUIFWidgetBase>> M_UIList;
	UPROPERTY()
	FDtUIStyle M_DefaultStyle;
};

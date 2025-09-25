// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class UDtRootViewport;
class UUIFWidgetBase;

/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	//注册UI
	void RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget);

	void UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget);
	

	
	UPROPERTY()
	TObjectPtr<UDtRootViewport> M_RootViewport;

private: 
	TArray<TWeakObjectPtr<UUIFWidgetBase>> M_UIList;
};

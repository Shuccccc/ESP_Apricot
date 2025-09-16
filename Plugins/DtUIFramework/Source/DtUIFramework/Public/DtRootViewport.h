// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DtRootViewport.generated.h"

/**
 * 
 */

class UCanvasPanel; 
class UUILayerBase;

UCLASS(NotBlueprintable)
class DTUIFRAMEWORK_API UDtRootViewport : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	

	

	UPROPERTY()//根面板
	TObjectPtr<UCanvasPanel> M_RootViewport;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase> M_StaticLayer;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase> M_WindowLayer;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase>M_NotificationLayer;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase> M_PopupLayer;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase> M_ProgressLayer;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase> M_SystemLayer;
	
	UPROPERTY()
	TObjectPtr<UUILayerBase> M_TopLayer;
	
};

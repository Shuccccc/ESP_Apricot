// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UILayerBase.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS(NotBlueprintable)
class UILAYER_API UUILayerBase : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	UPROPERTY()
	TObjectPtr<UCanvasPanel> M_RootViewport;
	
	virtual void SetAnchorPoint();
};

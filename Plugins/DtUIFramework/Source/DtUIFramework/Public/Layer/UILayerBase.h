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
class DTUIFRAMEWORK_API UUILayerBase : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddWidgetToCanvas(UUserWidget* Widget) const;
	
	virtual bool Initialize() override;

	UPROPERTY()
	TObjectPtr<UCanvasPanel> M_RootViewport;
	
	virtual void SetAnchorPoint();
};

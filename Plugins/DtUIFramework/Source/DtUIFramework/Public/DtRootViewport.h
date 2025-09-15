// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "DtRootViewport.generated.h"

/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UDtRootViewport : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> RootViewport; 
};

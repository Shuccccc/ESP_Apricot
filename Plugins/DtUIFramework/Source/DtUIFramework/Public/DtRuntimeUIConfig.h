// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtRuntimeUIConfig.generated.h"

class UUIFWidgetBase;
/**
 * 
 */
UCLASS(config = DtUIFramework, DefaultConfig)
class DTUIFRAMEWORK_API UDtRuntimeUIConfig : public UObject
{
	GENERATED_BODY()


	public:
	
	UPROPERTY(config, EditAnywhere, Category = "Core Blueprint Widgets", meta = (DisplayName = "Window"))
	TSoftClassPtr<UUIFWidgetBase> UMG_Window;

	UPROPERTY(config, EditAnywhere, Category = "Core Blueprint Widgets", meta = (DisplayName = "Window"))
	TSubclassOf<UUIFWidgetBase> UMG_WindowBar;

};

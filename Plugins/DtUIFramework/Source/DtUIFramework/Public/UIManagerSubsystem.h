// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"


class UDtRootViewport;
/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	
	UFUNCTION(BlueprintCallable)
	void InitUIManager();

	UPROPERTY()
	TObjectPtr<UDtRootViewport> M_RootViewport;

	
	
};

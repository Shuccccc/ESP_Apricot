// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class UDtRootViewport;
/**
 * 
 */
UCLASS()
class DTUIFRAMEWORK_API UUIManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	
	UPROPERTY()
	TObjectPtr<UDtRootViewport> M_RootViewport;

};

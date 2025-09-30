// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtUIFStruct.h"
#include "Engine/Engine.h" 
#include "UIManager.generated.h"

class UDtRootViewport;
class UUIFWidgetBase;

/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam()
UCLASS()
class DTUIFRAMEWORK_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// UGameInstanceSubsystem的生命周期函数
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

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

	
	void OnWorldLoaded(UWorld* NewWorld);

protected:
	
	FDelegateHandle OnWorldLoadedDelegateHandle;
};
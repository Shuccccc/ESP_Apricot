// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtUIFStruct.h"
#include "DtUIManagerSubsystem.generated.h"

class UDtRootViewport;
class UUIFWidgetBase;
class UDtUIFrameworkConfig;
class UUIFWidgetWindowBase ;
/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam()
UCLASS()
class DTUIFRAMEWORK_API UDtUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
//Blueprint

	UFUNCTION( BlueprintCallable , Category = "Blueprint | Window")
	UUIFWidgetWindowBase* GetWindow(FString ID);

	
	UFUNCTION(BlueprintCallable)
	void SetTheme(FDtUIStyle Style);
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FDtUIStyle GetUIStyle();
//Function
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/*
	void RegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget);
	void UnRegisterUI(TWeakObjectPtr<UUIFWidgetBase> InWidget);
	*/

	FDtUIStyle GetDefaultStyle();
	
	UPROPERTY()
	TObjectPtr<UDtRootViewport> M_RootViewport;

	void OnWorldLoaded(UWorld* NewWorld);

private:
	
	UPROPERTY()
	TArray<TWeakObjectPtr<UUIFWidgetBase>> M_UIList;
	UPROPERTY()
	FDtUIStyle M_DefaultStyle;
	
	UPROPERTY()
	FDtUIStyle M_CurrentStyle;
	
	UPROPERTY()
	UWorld*	M_World;
	
	//Blueprint类缓存
	
	void InitBlueprintCache();
	void OnBlueprintClassesLoaded();


	bool bIsCoreUIInitialized = false;
	
public:
	
	UPROPERTY()
	TSubclassOf<UUIFWidgetBase> M_UMG_Window;
	UPROPERTY()
	TSubclassOf<UUIFWidgetBase> M_UMG_WindowBar;

	
protected:
	
	FDelegateHandle OnWorldLoadedDelegateHandle;
};
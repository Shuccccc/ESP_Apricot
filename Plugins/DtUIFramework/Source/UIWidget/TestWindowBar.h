// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestWindowBar.generated.h"

class UScrollBox;
class UButton;
class UInvalidationBox;
class UOverlay;
class UImage;
/**
 * 
 */
UCLASS()
class UIWIDGET_API UTestWindowBar : public UUserWidget
{
	GENERATED_BODY()
public :
	virtual bool Initialize() override;


	
private:
	
	UPROPERTY()//根面板
	TObjectPtr<UOverlay> M_RootPanel;
	UPROPERTY()
	TObjectPtr<UImage> M_BG_Left;
	UPROPERTY()
	TObjectPtr<UImage> M_BG_Mind;
	UPROPERTY()
	TObjectPtr<UImage> M_BG_Right;
	UPROPERTY()
	TObjectPtr<UInvalidationBox> M_BD_InvalidBox;
	UPROPERTY()
	TObjectPtr<UButton> M_FN_DragButton;
	UPROPERTY()
	TObjectPtr<UScrollBox> M_CT_ScrollBox;

	void LodAsset();
private:
	

	




	
};

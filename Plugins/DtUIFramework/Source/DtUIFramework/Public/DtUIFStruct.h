// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtUIFStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDtUIStyle : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FLinearColor PrimaryColor = FColor::FromHex(TEXT("222222FF"));	// 主要颜色
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FLinearColor SecondaryColor = FColor::FromHex(TEXT("3489F9FF"));	// 次要颜色
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FLinearColor TertiaryColor = FColor::FromHex(TEXT("F9F9F9FF")); 	// 第三颜色
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FLinearColor AccentColor = FColor::FromHex(TEXT("F95757FF"));	// 强调色
};

UENUM()
enum class EDtUILayer : uint8
{
	Static,
	Floating,
	Window,
	Notification,
	Popup,
	Progress,
	System,
	Top
};

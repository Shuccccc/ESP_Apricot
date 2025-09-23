// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DtUIFStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDtUIStyle
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FLinearColor PrimaryColor = FColor::FromHex(TEXT("222222FF"));	// 主要颜色
	UPROPERTY(BlueprintReadWrite)
	FLinearColor SecondaryColor = FColor::FromHex(TEXT("3489F9FF"));	// 次要颜色
	UPROPERTY(BlueprintReadWrite)
	FLinearColor TertiaryColor = FColor::FromHex(TEXT("F9F9F9FF")); 	// 第三颜色
	UPROPERTY(BlueprintReadWrite)
	FLinearColor AccentColor = FColor::FromHex(TEXT("F95757FF"));	// 强调色
	UPROPERTY(BlueprintReadWrite)
	FLinearColor ComponentColor = FColor::FromHex(TEXT("F95757FF"));	// 组件颜色
	UPROPERTY(BlueprintReadWrite)
	FLinearColor ComponentSecondaryColor = FColor::FromHex(TEXT("F9F9F9FF")); // 组件次要颜色
};
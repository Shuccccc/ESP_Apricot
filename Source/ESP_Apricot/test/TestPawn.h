// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TestPawn.generated.h"

UCLASS()
class ESP_APRICOT_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPawn();
	
	// 输入事件处理函数
	UFUNCTION()
	void OnPanStarted(const FInputActionValue& Value);
	UFUNCTION()
	void OnPanTriggered(const FInputActionValue& Value);
	UFUNCTION()
	void OnPanCompleted(const FInputActionValue& Value);
	UFUNCTION()
	void OnPanOngoing(const FInputActionValue& Value);

	UFUNCTION()
	void OnRotateStarted(const FInputActionValue& Value);
	UFUNCTION()
	void OnRotateTriggered(const FInputActionValue& Value);
	UFUNCTION()
	void OnRotateCompleted(const FInputActionValue& Value);
	UFUNCTION()
	void OnRotateOngoing(const FInputActionValue& Value);
	// 输入动作指针（需与内容浏览器中的资产名称一致）
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Pan;  // 平移动作

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Rotate;  // 旋转动作

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Zoom;  // 缩放动作
	
	// UFUNCTION()
	// void OnZoom(float Value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> ViewMappingContext;

	FVector PanDirection;
	float RotateSpeed = 100.0f;
	float ZoomSpeed = 100.0f;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
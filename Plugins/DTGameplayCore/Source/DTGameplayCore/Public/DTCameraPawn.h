// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "DtCameraPawn.generated.h"

//前向声明
class UStaticMeshComponent ;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UEnhancedInputComponent;
UCLASS()
class DTGAMEPLAYCORE_API ADtCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADtCameraPawn();

//组件
	UPROPERTY(BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UStaticMeshComponent> PC_RootMesh;
	
	UPROPERTY(BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<USpringArmComponent> PC_SpringArm;
	
	UPROPERTY(BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UCameraComponent> PC_PawnCamera;
	
	UPROPERTY(BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UArrowComponent> PC_Arrow;
	
	UPROPERTY(BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UFloatingPawnMovement> PC_Movement;
	
//增强输入
	UPROPERTY(BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UEnhancedInputComponent> EnhancedInput;  // 平移
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputAction> IA_Combo_move;  // 平移

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputAction> IA_Combo_rotate;  // 旋转

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputAction> IA_Move;  // 获取数值
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputAction> IA_Zoom;  // 缩放
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> ViewMappingContext;
	
//设置属性

	// 摄像机相关设置
	//最大视角限制
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_ViewPitchMax = -5.f;
	//最小视角限制
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_ViewPitchMin = -60.f;
	//摄像机旋转缓动
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_CameraRotationLagSpeed = 16.f;
	//最大摄像机臂长度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_MaxSpringArmLength = 5000.f;
	//最小摄像机臂长度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_MinSpringArmLength = 300.f;
	//摄像机臂长度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_InitialSpringArmLength = 3000.f;
	//摄像机初始Pitch(Add)
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings")
	float C_InitialPitchInput = 15.f;

// 移动输入缩放因子
	//向前输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "DefaultProperty|InputSettings")
	float I_ForwardMovementScale = 2.f;
	//左右输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|InputSettings")
	float I_RightMovementScale = 1.f;
	//Pitch输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|InputSettings")
	float I_PitchInputScale = 2.f;
	//Yaw输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|InputSettings")
	float I_YawInputScale = 2.f;
	//Zoom输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "DefaultProperty|InputSettings")
	float I_ZoomScale = 40.f;

	// Pawn移动组件设置
	//Pawn移动最大速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings")
	float P_MaxSpeed = 4800.f;
	//Pawn移动加速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings")
	float P_Acceleration = 48000.f;
	//Pawn移动减速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings")
	float P_Deceleration = 12000.f;
	//Pawn旋转时加速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings")
	float P_TurningBoost = 8.f;
	
	//增强输入::CallBack
	UFUNCTION()
	void OnMoveOngoing(const FInputActionValue& Value);
	UFUNCTION()
	void OnRotateOngoing(const FInputActionValue& Value);
	UFUNCTION()
	void OnZoomTriggered(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

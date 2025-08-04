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

USTRUCT(BlueprintType)
struct FCameraBounds 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D Max = FVector2D(0.f);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D Min = FVector2D(0.f);
	//初始化
	FCameraBounds() = default;
	FCameraBounds(float Max_X, float Max_Y, float Min_X, float Min_Y): Max(Max_X, Max_Y), Min(Min_X, Min_Y){};
	FCameraBounds(FVector2D Max, FVector2D Min): Max(Max), Min(Min){};
};
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
	//最大视角限制 //EditCondition = “isController”
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "限制最大Pitch"))
	float C_ViewPitchMax = -5.f;
	//最小视角限制
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "限制最小Pitch"))
	float C_ViewPitchMin = -60.f;
	//摄像机边界限制
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "限制摄像机边界"))
	FCameraBounds C_CameraBounds = FCameraBounds(168000.f, 168000.f, -168000.f, -168000.f);
	//最大摄像机臂长度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "最大摄像机臂长度"))
	float C_MaxSpringArmLength = 5000.f;
	//最小摄像机臂长度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "最小摄像机臂长度"))
	float C_MinSpringArmLength = 300.f;
	//摄像机臂长度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "摄像机臂长度"))
	float C_InitialSpringArmLength = 3000.f;
	//摄像机初始Pitch(Add)
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "摄像机初始旋转"))
	float C_InitialPitchInput = 15.f;
	//摄像机旋转缓动
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|CameraSettings", meta = (DisplayName = "摄像机旋转延迟"))
	float C_CameraRotationLagSpeed = 16.f;
	
// 移动输入缩放因子
	//向前输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "DefaultProperty|InputSettings", meta = (DisplayName = "摄像机移动速度(向前)"))
	float I_ForwardMovementScale = 2.f;
	//左右输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|InputSettings", meta = (DisplayName = "摄像机移动速度(左右)"))
	float I_RightMovementScale = 1.f;
	//Pitch输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|InputSettings", meta = (DisplayName = "摄像机旋转速度(Pitch)"))
	float I_PitchInputScale = 2.f;
	//Yaw输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|InputSettings", meta = (DisplayName = "摄像机旋转速度(Yaw)"))
	float I_YawInputScale = 2.f;
	//Zoom输入缩放因子
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "DefaultProperty|InputSettings", meta = (DisplayName = "视角缩放速度"))
	float I_ZoomScale = 40.f;

	// Pawn移动组件设置
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings", meta = (DisplayName = "设置Pwan"))
	bool SetPawnDef = false;
	//Pawn移动最大速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings", meta = (DisplayName = "Pawn移动最大速度",EditCondition="SetPawnDef"))
	float P_MaxSpeed = 4800.f;
	//Pawn移动加速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings", meta = (DisplayName = "Pawn移动加速度",EditCondition="SetPawnDef"))
	float P_Acceleration = 48000.f;
	//Pawn移动减速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings", meta = (DisplayName = "Pawn移动减速度",EditCondition="SetPawnDef"))
	float P_Deceleration = 12000.f;
	//Pawn旋转时加速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefaultProperty|MovementSettings", meta = (DisplayName = "Pawn旋转时加速度",EditCondition="SetPawnDef"))
	float P_TurningBoost = 8.f;
	
	//增强输入::CallBack
	UFUNCTION()
	void OnMoveOngoing(const FInputActionValue& Value);
	UFUNCTION()
	void OnRotateOngoing(const FInputActionValue& Value);
	UFUNCTION()
	void OnZoomTriggered(const FInputActionValue& Value);
	void test();
private:
	UPROPERTY(Transient)
	FVector3d M_MoveForward ;
	UPROPERTY(Transient)
	FVector3d M_MoveRight ;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "DtCameraPawn.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADtCameraPawn::ADtCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//初始化组件
	PC_RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PC_RootMesh"));
	PC_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PC_SpringArm"));
	PC_PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PC_PawnCamera"));
	PC_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("PC_Arrow"));
	//设置组件层级
	SetRootComponent(PC_RootMesh);
	PC_SpringArm->SetupAttachment(PC_RootMesh);
	PC_PawnCamera->SetupAttachment(PC_SpringArm);
	PC_Arrow->SetupAttachment(PC_RootMesh);
}



// Called when the game starts or when spawned
void ADtCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// 初始化增强输入子系统
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (ViewMappingContext)
		{
			Subsystem->AddMappingContext(ViewMappingContext, 0);
		}
	}
	
	//设置属性
	//Pawn
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	PC_SpringArm->bDoCollisionTest = false;
	//限制摄像机视角
	APlayerCameraManager* PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	PlayerCameraManager->ViewPitchMax = C_ViewPitchMax;
	PlayerCameraManager->ViewPitchMin = C_ViewPitchMin;
	//摄像机转动延迟
	PC_SpringArm->bEnableCameraRotationLag = true;
	PC_SpringArm->CameraRotationLagSpeed = C_CameraRotationLagSpeed;

	//移动延迟

	PC_SpringArm->bEnableCameraLag = true;
	PC_SpringArm->CameraLagSpeed = 24;
	PC_SpringArm->CameraLagMaxDistance = 640; // 限制最大滞后距离

	//摄像机初始位置;
	//PC_SpringArm->TargetArmLength = C_InitialSpringArmLength;
	M_TargetSpringArmLength = C_InitialSpringArmLength; // 初始化目标臂长
	M_TargetRotation.Pitch = C_InitialPitchInput;

	
	GetController()->SetControlRotation(M_TargetRotation);
	
	//M_NormalizedArmLength = FMath::Clamp((PC_SpringArm->TargetArmLength ) / (C_MaxSpringArmLength - C_MinSpringArmLength), 0.0f, 1.0f);

}

// 绑定增强输入
void ADtCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(IA_Combo_move, ETriggerEvent::Ongoing, this, &ADtCameraPawn::OnMoveOngoing);

	EnhancedInput->BindAction(IA_Combo_rotate, ETriggerEvent::Ongoing, this, &ADtCameraPawn::OnRotateOngoing);

	EnhancedInput->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ADtCameraPawn::OnZoomTriggered);

	EnhancedInput->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &ADtCameraPawn::OnZoomCompleted);
	
	EnhancedInput->BindActionValue(IA_Move);
	
}

void ADtCameraPawn::OnMoveOngoing(const FInputActionValue& Value) 
{
	//获取IA_Move的值
	FVector2D MoveActionValue = EnhancedInput->GetBoundActionValue(IA_Move).Get<FVector2D>();
	
	// 根据摄像机臂长度动态调整移动速度
	float ZoomFactor = 1.0f + (8 * M_NormalizedArmLength);

	// 计算移动向量
	float ForwardMovement = MoveActionValue.Y * I_ForwardMovementScale * -1.f * ZoomFactor * 2;
	float RightMovement = MoveActionValue.X * I_RightMovementScale * -1.f * ZoomFactor;
	
	// 获取方向向量
	FVector ForwardDirection = GetActorForwardVector();
	FVector RightDirection = GetActorRightVector();
	
	// 计算目标移动向量
	FVector TargetMovement = (ForwardDirection * ForwardMovement) + (RightDirection * RightMovement);
	
	TargetMovement.Z = 0.f;
	SetActorLocation(GetActorLocation() + TargetMovement);
}

void ADtCameraPawn::OnRotateOngoing(const FInputActionValue& Value)
{
	//获取IA_Move的值
	const FVector2D MoveActionValue = EnhancedInput->GetBoundActionValue(IA_Move).Get<FVector2D>();

	M_TargetRotation = GetControlRotation();
	
	//纵向旋转
	M_TargetRotation.Pitch = FMath::Clamp(M_TargetRotation.Pitch + (MoveActionValue.Y * I_PitchInputScale), C_ViewPitchMin, C_ViewPitchMax);
	//横向旋转
	M_TargetRotation.Yaw += MoveActionValue.X * I_YawInputScale ;
	
	// 设置目标旋转
	GetController()->SetControlRotation(M_TargetRotation);

}

void ADtCameraPawn::OnZoomTriggered(const FInputActionValue& Value)
{
	bIsZooming = true;
	// 计算新的目标臂长
	float NewTargetArmLength = M_TargetSpringArmLength + Value.Get<float>()*I_ZoomScale;
	M_TargetSpringArmLength = FMath::Clamp(NewTargetArmLength, C_MinSpringArmLength, C_MaxSpringArmLength);
	
	bIsZooming = true;
	
	M_NormalizedArmLength = FMath::Clamp((PC_SpringArm->TargetArmLength ) / (C_MaxSpringArmLength - C_MinSpringArmLength), 0.0f, 1.0f);
	//PC_Movement->Deceleration =  P_Deceleration * (1 - M_NormalizedArmLength);
}

void ADtCameraPawn::OnZoomCompleted(const FInputActionValue& Value)
{
	//bIsZooming = false;
}


// Called every frame
void ADtCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//摄像机臂平滑
	if (bIsZooming)
	{
		PC_SpringArm->TargetArmLength = FMath::FInterpTo(PC_SpringArm->TargetArmLength, M_TargetSpringArmLength, DeltaTime, ZoomInterpSpeed);

		if (FMath::IsNearlyEqual(PC_SpringArm->TargetArmLength, M_TargetSpringArmLength, 0.1f))
		{
			PC_SpringArm->TargetArmLength = M_TargetSpringArmLength;
			bIsZooming = false;
		}
	}
	
}



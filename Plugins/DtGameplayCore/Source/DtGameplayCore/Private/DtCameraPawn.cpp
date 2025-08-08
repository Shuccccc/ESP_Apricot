// Fill out your copyright notice in the Description page of Project Settings.


#include "DtCameraPawn.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
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
	//Pawn移动组件
	PC_Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PC_Movement"));
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
	/*摄像机臂延迟
	PC_SpringArm->bEnableCameraLag = true;
	PC_SpringArm->CameraLagSpeed = 100;
	PC_SpringArm->CameraLagMaxDistance = 1000.0f; // 限制最大滞后距离
	*/
	//摄像机初始位置;
	PC_SpringArm->TargetArmLength = C_InitialSpringArmLength;
	M_TargetSpringArmLength = C_InitialSpringArmLength; // 初始化目标臂长
	AddControllerPitchInput(C_InitialPitchInput);
	//Pawn移动组件
	PC_Movement->MaxSpeed = P_MaxSpeed;
	PC_Movement->Acceleration= P_Acceleration;
	PC_Movement->Deceleration = P_Deceleration;
	PC_Movement->TurningBoost = P_TurningBoost;
	
}

// 绑定增强输入
void ADtCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(IA_Combo_move, ETriggerEvent::Ongoing, this, &ADtCameraPawn::OnMoveOngoing);

	EnhancedInput->BindAction(IA_Combo_rotate, ETriggerEvent::Ongoing, this, &ADtCameraPawn::OnRotateOngoing);

	EnhancedInput->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ADtCameraPawn::OnZoomTriggered);
	
	EnhancedInput->BindActionValue(IA_Move);
	
}

void ADtCameraPawn::OnMoveOngoing(const FInputActionValue& Value) 
{
	//获取IA_Move的值
	FVector2D MoveActionValue = EnhancedInput->GetBoundActionValue(IA_Move).Get<FVector2D>();
	//获取方向
	FVector3d MoveForward = GetActorForwardVector();
	FVector3d MoveRight = GetActorRightVector();

	PC_Movement->AddInputVector(FVector{MoveForward.X * MoveActionValue.Y * I_ForwardMovementScale * -1.f,MoveForward.Y * MoveActionValue.Y * I_ForwardMovementScale * -1.f,0.f},true);
	
	PC_Movement->AddInputVector(FVector{MoveRight.X * MoveActionValue.X * I_RightMovementScale * -1.f,MoveRight.Y * MoveActionValue.X * I_RightMovementScale * -1.f,0.f},true);
	
	//PC_Movement有隧穿 需要用碰撞限制移动
}

void ADtCameraPawn::OnRotateOngoing(const FInputActionValue& Value)
{
	//获取IA_Move的值
	const FVector2D MoveActionValue = EnhancedInput->GetBoundActionValue(IA_Move).Get<FVector2D>();
	//纵向旋转
	AddControllerPitchInput(MoveActionValue.Y * I_PitchInputScale * -1.f);
	AddControllerYawInput(MoveActionValue.X * I_YawInputScale);
}

void ADtCameraPawn::OnZoomTriggered(const FInputActionValue& Value)
{
	// 计算新的目标臂长
	float NewTargetArmLength = M_TargetSpringArmLength + Value.Get<float>()*I_ZoomScale;
	NewTargetArmLength = FMath::Clamp(NewTargetArmLength, C_MinSpringArmLength, C_MaxSpringArmLength);
	
	// 设置目标臂长
	M_TargetSpringArmLength = NewTargetArmLength;
	bIsZooming = true;
}

void ADtCameraPawn::UpdateZoomSmoothing(float DeltaTime)
{
	if (PC_SpringArm || bIsZooming)
	{
		PC_SpringArm->TargetArmLength = FMath::FInterpTo(PC_SpringArm->TargetArmLength, M_TargetSpringArmLength, DeltaTime, ZoomInterpSpeed);
	
		if (FMath::IsNearlyEqual(PC_SpringArm->TargetArmLength, M_TargetSpringArmLength, 0.1f))
		{
			PC_SpringArm->TargetArmLength = M_TargetSpringArmLength;
			bIsZooming = false;
		}
	}
}

// Called every frame
void ADtCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateZoomSmoothing(DeltaTime);

}



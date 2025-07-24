// Fill out your copyright notice in the Description page of Project Settings.


#include "DTCameraPawn.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADTCameraPawn::ADTCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
void ADTCameraPawn::BeginPlay()
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
	
	//限制摄像机视角
	APlayerCameraManager* PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	PlayerCameraManager->ViewPitchMax = -5.f;
	PlayerCameraManager->ViewPitchMin = -60.f;
	//摄像机转动延迟
	PC_SpringArm->bEnableCameraRotationLag = true;
	PC_SpringArm->CameraRotationLagSpeed = 16.f;
	//摄像机初始位置
	AddControllerPitchInput(-35.f);
	PC_SpringArm->TargetArmLength = 3000.f;
	//Pawn移动组件
	PC_Movement->MaxSpeed = 4800.f;
	PC_Movement->Acceleration= 48000.f;
	PC_Movement->Deceleration = 12000.f;
	PC_Movement->TurningBoost = 8.f;
	
}

// 绑定增强输入
void ADTCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(IA_Combo_move, ETriggerEvent::Ongoing, this, &ADTCameraPawn::OnMoveOngoing);

	EnhancedInput->BindAction(IA_Combo_rotate, ETriggerEvent::Ongoing, this, &ADTCameraPawn::OnRotateOngoing);

	EnhancedInput->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ADTCameraPawn::OnZoomTriggered);
	
	EnhancedInput->BindActionValue(IA_Move);
	
}
void ADTCameraPawn::OnMoveOngoing(const FInputActionValue& Value) 
{
	//获取IA_Move的值
	FVector2D MoveActionValue = EnhancedInput->GetBoundActionValue(IA_Move).Get<FVector2D>();
	//获取方向
	FVector3d MoveForward = GetActorForwardVector();
	FVector3d MoveRight = GetActorRightVector();
	//前后移动
	PC_Movement->AddInputVector(FVector{MoveForward.X*MoveActionValue.Y*-2.f , MoveForward.Y*MoveActionValue.Y*-2.f, 0});
	//左右移动
	PC_Movement->AddInputVector(FVector{MoveRight.X*MoveActionValue.X*-1.f, MoveRight.Y*MoveActionValue.X*-1.f, 0});	

}

void ADTCameraPawn::OnRotateOngoing(const FInputActionValue& Value)
{
	//获取IA_Move的值
	const FVector2D MoveActionValue = EnhancedInput->GetBoundActionValue(IA_Move).Get<FVector2D>();
	//纵向旋转
	AddControllerPitchInput(MoveActionValue.Y*-2.f);
	AddControllerYawInput(MoveActionValue.X*2.f);
}

void ADTCameraPawn::OnZoomTriggered(const FInputActionValue& Value)
{
	PC_SpringArm->TargetArmLength += Value.Get<float>()*20.f;
}

// Called every frame
void ADTCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"


// Sets default values
ATestPawn::ATestPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input

void ATestPawn::BeginPlay()
{
    Super::BeginPlay();
    // 初始化增强输入子系统
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
        if (ViewMappingContext)
        {
            Subsystem->AddMappingContext(ViewMappingContext, 0);
        }
    }
}

void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInput)
    {
        // 绑定输入事件
        EnhancedInput->BindAction(IA_Pan, ETriggerEvent::Started, this, &ATestPawn::OnPanStarted);
        EnhancedInput->BindAction(IA_Pan, ETriggerEvent::Triggered, this, &ATestPawn::OnPanTriggered);
        EnhancedInput->BindAction(IA_Pan, ETriggerEvent::Completed, this, &ATestPawn::OnPanCompleted);
        EnhancedInput->BindAction(IA_Pan, ETriggerEvent::Ongoing, this, &ATestPawn::OnPanCompleted);

        EnhancedInput->BindAction(IA_Rotate, ETriggerEvent::Started, this, &ATestPawn::OnRotateStarted);
        EnhancedInput->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &ATestPawn::OnRotateTriggered);
        EnhancedInput->BindAction(IA_Rotate, ETriggerEvent::Completed, this, &ATestPawn::OnRotateCompleted);
        EnhancedInput->BindAction(IA_Rotate, ETriggerEvent::Ongoing, this, &ATestPawn::OnRotateCompleted);

    //    EnhancedInput->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ATestPawn::OnZoom);
    }
}

// 平移逻辑（左键拖动）
void ATestPawn::OnPanStarted(const FInputActionValue& Value) { /* 初始化拖动状态 */ }
void ATestPawn::OnPanTriggered(const FInputActionValue& Value)
{
    GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("OnPanTriggered"));

    FVector2D Delta = Value.Get<FVector2D>();
    PanDirection = FVector(Delta.Y, Delta.X, 0);
    AddActorWorldOffset(PanDirection * RotateSpeed * GetWorld()->GetDeltaSeconds());
}
void ATestPawn::OnPanCompleted(const FInputActionValue& Value) { /* 重置拖动状态 */ }

// 旋转逻辑（右键拖动）
void ATestPawn::OnRotateStarted(const FInputActionValue& Value) { /* 初始化旋转状态 */ }
void ATestPawn::OnRotateTriggered(const FInputActionValue& Value)
{
    GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("OnRotateTriggered"));
    FVector2D Delta = Value.Get<FVector2D>();
    AddActorWorldRotation(FRotator(-Delta.Y * RotateSpeed, Delta.X * RotateSpeed, 0));
}
void ATestPawn::OnRotateCompleted(const FInputActionValue& Value) { /* 重置旋转状态 */ }

// 缩放逻辑（滚轮）
// void ATestPawn::OnZoom(float Value)
// {
//     float Delta = Value * ZoomSpeed;
//     // 假设使用SpringArm调整相机距离
//     if (USpringArmComponent* SpringArm = GetSpringArm())
//     {
//         SpringArm->TargetArmLength -= Delta;
//         SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 200.0f, 1000.0f);
//     }
// }
void ATestPawn::OnPanOngoing(const FInputActionValue& Value) { GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("OnPanOngoing"));/* 初始化拖动状态 */ }
void ATestPawn::OnRotateOngoing(const FInputActionValue& Value) {GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("OnRotateOngoing")); /* 初始化拖动状态 */ }
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "DTCameraPawn.generated.h"

//前向声明
class UStaticMeshComponent ;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UEnhancedInputComponent;
UCLASS()
class DTGAMEPLAYCORE_API ADTCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADTCameraPawn();

//组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UStaticMeshComponent> PC_RootMesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<USpringArmComponent> PC_SpringArm;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UCameraComponent> PC_PawnCamera;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PawnComponent")
	TObjectPtr<UArrowComponent> PC_Arrow;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PawnComponent")
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

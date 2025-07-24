// Fill out your copyright notice in the Description page of Project Settings.


#include "DTCameraPawn.h"


// Sets default values
ADTCameraPawn::ADTCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADTCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADTCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADTCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


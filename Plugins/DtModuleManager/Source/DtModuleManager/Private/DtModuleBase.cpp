// Fill out your copyright notice in the Description page of Project Settings.


#include "DtModuleBase.h"


void ADtModuleBase::ResetToDefault_Implementation()
{
	
}



// Sets default values
ADtModuleBase::ADtModuleBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
// Called when the game starts or when spawned
void ADtModuleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADtModuleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


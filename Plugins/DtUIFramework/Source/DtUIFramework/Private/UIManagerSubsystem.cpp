// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerSubsystem.h"
#include "DtRootViewport.h"

void UUIManagerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	M_RootViewport = CreateWidget<UDtRootViewport>(GetWorld(), UDtRootViewport::StaticClass());
	M_RootViewport->AddToViewport(8);
}

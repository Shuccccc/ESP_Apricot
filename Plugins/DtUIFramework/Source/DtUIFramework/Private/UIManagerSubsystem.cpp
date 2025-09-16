// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerSubsystem.h"
#include "DtRootViewport.h"

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//把DtRootViewport添加到视口
	M_RootViewport = CreateWidget<UDtRootViewport>(GetGameInstance(), UDtRootViewport::StaticClass());
	M_RootViewport->AddToViewport();
	
}

void UUIManagerSubsystem::InitUIManager()
{

	
}

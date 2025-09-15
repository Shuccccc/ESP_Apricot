// Fill out your copyright notice in the Description page of Project Settings.


#include "DtRootViewport.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"

bool UDtRootViewport::Initialize()
{
	RootViewport = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(),FName(TEXT("RootViewport")));

	WidgetTree->RootWidget = RootViewport;
	
	return Super::Initialize();

}

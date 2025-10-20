// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UIFWidgetWindowBase.h"

#include "Layer/UIWindowLayer.h"

void UUIFWidgetWindowBase::WindowActionRequested_Implementation(EDtWindowAction Action)
{
}

void UUIFWidgetWindowBase::OnWindowActionReceived(UUIFWidgetBase* TargetWindow, EDtWindowAction Action)
{
}

void UUIFWidgetWindowBase::CloseWindowBeginNative_Implementation()
{
	OwningLayerPtr.Get()->RemoveWindow(PrivateID);
}

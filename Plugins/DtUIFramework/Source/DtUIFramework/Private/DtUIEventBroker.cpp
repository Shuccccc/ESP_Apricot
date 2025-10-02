// Fill out your copyright notice in the Description page of Project Settings.


#include "DtUIEventBroker.h"

void UDtUIEventBroker::WindowCreatedBroadcast(UUIFWidgetBase* CreatedWindow)
{
	OnWindowCreated.Broadcast(CreatedWindow);
}

void UDtUIEventBroker::WindowDestroyedBroadcast(UUIFWidgetBase* CreatedWindow)
{
	OnWindowDestroyed.Broadcast(CreatedWindow);
}

void UDtUIEventBroker::WindowStateChangedBroadcast(UUIFWidgetBase* CreatedWindow, EDtWindowAction Action)
{
	OnWindowStateChanged.Broadcast(CreatedWindow,Action);
}

void UDtUIEventBroker::WindowActionRequestedBroadcast(UUIFWidgetBase* CreatedWindow, EDtWindowAction Action)
{
	OnWindowActionRequested.Broadcast(CreatedWindow,Action);
}

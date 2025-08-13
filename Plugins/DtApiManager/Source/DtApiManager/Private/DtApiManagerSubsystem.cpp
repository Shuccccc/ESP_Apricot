// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubsystem.h"

bool UDtApiManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UDtApiManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


}

void UDtApiManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

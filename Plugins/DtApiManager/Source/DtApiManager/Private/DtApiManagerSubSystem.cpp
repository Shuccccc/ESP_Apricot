// Fill out your copyright notice in the Description page of Project Settings.


#include "DtApiManagerSubSystem.h"

bool UDtApiManagerSubSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UDtApiManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


}

void UDtApiManagerSubSystem::Deinitialize()
{
	Super::Deinitialize();
}

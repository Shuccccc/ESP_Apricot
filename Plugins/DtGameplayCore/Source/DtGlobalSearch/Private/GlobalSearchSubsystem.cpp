// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalSearchSubsystem.h"

void UGlobalSearchSubsystem::RegisterToGlobalSearch(UObject* GlobalSearchObject, FString GlobalSearchName,
	FString GlobalSearchDescription)
{
}

void UGlobalSearchSubsystem::UnRegisterFromGlobalSearch(UObject* M_GlobalSearchObject, FString M_GlobalSearchName)
{
}

TSubclassOf<UObject> UGlobalSearchSubsystem::GlobalSearchByName(FString Name)
{
	return nullptr;
}

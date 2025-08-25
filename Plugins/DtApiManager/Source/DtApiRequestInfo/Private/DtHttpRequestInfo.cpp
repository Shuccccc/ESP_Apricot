// Fill out your copyright notice in the Description page of Project Settings.


#include "DtHttpRequestInfo.h"
#include "DtApiManagerSubsystem.h"


void UDtHttpRequestInfo::SenHttpRequest(RequestDataObject& RequestDataObject)
{
	bool bSucces = false;
	
//	UDtApiManagerSubsystem* DtApiManagerSubsystem = CastChecked<UDtApiManagerSubsystem>(USubsystemBlueprintLibrary::GetEngineSubsystem(UDtApiManagerSubsystem::StaticClass()));
	auto* GameInstance = GetWorld();
if (GameInstance)
{
	UDtApiManagerSubsystem* DtApiManagerSubsystem = GameInstance->GetSubsystem<UDtApiManagerSubsystem>();
	
	if (! DtApiManagerSubsystem)
	{
		return;
	}
	
	FString RequestUrl = DtApiManagerSubsystem->GetApiUrlForKey(RequestDataObject , bSucces);
	
	if (!bSucces)
	{
		RequestDataObject.CallBack.ExecuteIfBound(FHttpRequestPtr{}, FHttpResponsePtr{}, false );
	}
}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DtHttpRequestInfo.h"
#include "DtApiManagerSubsystem.h"
#include "K2Node_GetSubsystem.h"


void UDtHttpRequestInfo::SenHttpRequest(RequestDataObject& RequestDataObject)
{
	bool bSucces = false;
	
	UDtApiManagerSubsystem* DtApiManagerSubsystem = GEngine->GetEngineSubsystem<UDtApiManagerSubsystem>();
	
	FString RequestUrl = DtApiManagerSubsystem->GetApiUrlForKey(RequestDataObject , &bSucces);
	
	if (!bSucces)
	{
		if (RequestDataObject.CallBack)
		{
			RequestDataObject.CallBack(RequestDataObject.Object, RequestDataObject);
		}
		return;
	}
	
	
}

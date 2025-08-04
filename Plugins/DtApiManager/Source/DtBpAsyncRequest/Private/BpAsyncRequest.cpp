// Fill out your copyright notice in the Description page of Project Settings.


#include "BpAsyncRequest.h"

UBpAsyncRequest* UBpAsyncRequest::CreateAsyncRequest(UObject* WorldContextObject, FString Url,
	TMap<FString, FString> Headers, TMap<FString, FString> Params, TMap<FString, FString> Body)
{
	UBpAsyncRequest* AsyncAction = NewObject<UBpAsyncRequest>();
	AsyncAction->M_WorldContextObject = WorldContextObject;
	AsyncAction->M_URL = MoveTemp(Url); 
	AsyncAction->M_Headers = MoveTemp(Headers);
	AsyncAction->M_Params = MoveTemp(Params);
	AsyncAction->M_Body = MoveTemp(Body);
	return AsyncAction;
	
}

void UBpAsyncRequest::Activate()
{
	Super::Activate();
}

void UBpAsyncRequest::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
}

UBpAsyncRequest::UBpAsyncRequest()
{
}

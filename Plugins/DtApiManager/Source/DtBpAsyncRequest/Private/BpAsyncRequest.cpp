// Fill out your copyright notice in the Description page of Project Settings.


#include "BpAsyncRequest.h"

#include "DtBpAsyncRequest.h"
#include "Http.h"

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

//SendHttp

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UBpAsyncRequest::OnHttpRequestCompleted);
	Request->SetURL(M_URL);
	Request->SetVerb("GET");
	Request->ProcessRequest();
	
}

void UBpAsyncRequest::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	if (!Response.IsValid())
	{
		OnFail.Broadcast(false, TEXT("HTTP Error: Response is not valid"),-1);
		UE_LOG(LogBpAsyncRequest, Error, TEXT("HTTP Error: Response is not valid"));
		return;
	}
	
	int32 ResponseCode = Response->GetResponseCode();
	FString ResponseContent = Response->GetContentAsString();
	
	if (ResponseCode == 200)
	{
		OnCompleted.Broadcast(true, ResponseContent, ResponseCode);
		UE_LOG(LogBpAsyncRequest, Log, TEXT("Request: %s "), *Request->GetURL());
	}
	else
	{
		OnFail.Broadcast(false, ResponseContent , ResponseCode );
	}
	
}

UBpAsyncRequest::UBpAsyncRequest()
{
}

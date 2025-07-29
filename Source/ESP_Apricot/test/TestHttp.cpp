// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHttp.h"
#include "Http.h"
#include "Reflection/FunctionUtils.h"

UTestHttp::UTestHttp()
{
}

UTestHttp* UTestHttp::TestHttpAsyncAction(UObject* WorldContextObject, FString URL , TMap<FString,FString> Headers, TMap<FString,FString> Params,TMap<FString,FString> Body)
{
	UTestHttp* AsyncAction = NewObject<UTestHttp>();
	AsyncAction->M_WorldContextObject = WorldContextObject;
	AsyncAction->M_URL = MoveTemp(URL); 
	AsyncAction->M_Headers = MoveTemp(Headers);
	AsyncAction->M_Params = MoveTemp(Params);
	AsyncAction->M_Body = MoveTemp(Body);
	return AsyncAction;
}

void UTestHttp::Activate()
{
	Super::Activate();
//	Async(EAsyncExecution::Thread , [this](){});
	
	RegisterWithGameInstance(M_WorldContextObject);
	
	SendHttp(M_URL);
}



void UTestHttp::OnHttpRequestCompleted( FHttpRequestPtr Request,UE::Reflection::, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	// 检查 Response 是否有效
	if (bWasSuccessful && Response.IsValid() && Request->GetStatus() == EHttpRequestStatus::Succeeded)
	{
		int32 ResponseCode = Response->GetResponseCode();
		FString ResponseContent = Response->GetContentAsString();
        
		if (ResponseCode == 200)
		{
			OnCompleted.Broadcast(true, ResponseCode, ResponseContent);
		}
		else
		{
			OnFail.Broadcast(false, ResponseCode, FString::Printf(TEXT("HTTP Error: %d, Content: %s"), ResponseCode, *ResponseContent));
		}
	}
	else
	{
		FString ErrorMessage = TEXT("Request failed or invalid response");
		if (Request.IsValid())
		{
			ErrorMessage = FString::Printf(TEXT("Request failed - Status code: %d"), (int32)Request->GetStatus());
		}
		if (Response.IsValid())
		{
			ErrorMessage += FString::Printf(TEXT(", Code: %d, Content: %s"), 
			Response->GetResponseCode(), *Response->GetContentAsString());
		}
        
		OnFail.Broadcast(false, 0, ErrorMessage);
	}
	
	SetReadyToDestroy();
}


void UTestHttp::SendHttp(FString ServerURL)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UTestHttp::OnHttpRequestCompleted);
	Request->SetURL(ServerURL);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

/*
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ErrorMessage);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, 
	FString::Printf(TEXT("HTTP Request to: %s"), *M_URL));
*/
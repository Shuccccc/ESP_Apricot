// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHttp.h"
#include "Http.h"

UTestHttp::UTestHttp()
{
}

UTestHttp* UTestHttp::TestHttpAsyncAction(UObject* WorldContextObject, FString URL, HttpVerb Verb)
{
	UTestHttp* AsyncAction = NewObject<UTestHttp>();
	AsyncAction->M_URL = URL;
	AsyncAction->M_WorldContextObject = WorldContextObject;
	return AsyncAction;
}

void UTestHttp::Activate()
{
	Super::Activate();
	RegisterWithGameInstance(M_WorldContextObject);
    
	// 调试信息
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, 
		FString::Printf(TEXT("HTTP Request to: %s"), *M_URL));
    
	// 检查URL格式
	if (!M_URL.StartsWith(TEXT("http://")) && !M_URL.StartsWith(TEXT("https://")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, 
			FString::Printf(TEXT("Invalid URL format: %s"), *M_URL));
		OnFail.Broadcast(false, 0, TEXT("Invalid URL format"));
		SetReadyToDestroy();
		return;
	}
    
	SendHttp(M_URL);
}



void UTestHttp::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	// 检查 Response 是否有效
	if (bWasSuccessful && Response.IsValid() && Request->GetStatus() == EHttpRequestStatus::Succeeded)
	{
		int32 ResponseCode = Response->GetResponseCode();
		FString ResponseContent = Response->GetContentAsString();
        
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, 
			FString::Printf(TEXT("Success - Code: %d, Content Length: %d"), ResponseCode, ResponseContent.Len()));
        
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
        
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ErrorMessage);
		OnFail.Broadcast(false, 0, ErrorMessage);
	}
    
	SetReadyToDestroy();
}
void UTestHttp::OnHttpRequestReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
}

void UTestHttp::SendHttp(FString ServerURL)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UTestHttp::OnHttpRequestCompleted);
	Request->SetURL(ServerURL);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), TEXT("UnrealEngine/5.5"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));
	Request->ProcessRequest();
}


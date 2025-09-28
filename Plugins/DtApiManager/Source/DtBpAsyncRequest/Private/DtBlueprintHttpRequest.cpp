// Fill out your copyright notice in the Description page of Project Settings.


#include "DtBlueprintHttpRequest.h"
#include "DtHttpRequestInfo.h"
#include "Interfaces/IHttpResponse.h"


UDtBlueprintHttpRequest* UDtBlueprintHttpRequest::CreateAsyncRequest(UObject* WorldContextObject, FString RowName,TMap<FString, FString> Headers ,TMap<FString, FString> UrlParams, TMap<FString, FString> Body)
{
	UDtBlueprintHttpRequest* AsyncAction = NewObject<UDtBlueprintHttpRequest>();
	AsyncAction->M_WorldContextObject = WorldContextObject;
	AsyncAction->M_RequestData.RowKey = RowName;
	AsyncAction->M_RequestData.UrlParams = UrlParams;
	AsyncAction->M_RequestData.HeaderParams = Headers;
	AsyncAction->M_RequestData.BodyParams = Body;
	AsyncAction->M_RequestData.BodyJsonObject = NewObject<UVaRestJsonObject>();
	AsyncAction->M_RequestData.Object = AsyncAction;
	AsyncAction->M_RequestData.CallBack.BindUObject(AsyncAction,&UDtBlueprintHttpRequest::OnHttpRequestCompleted);
	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	return AsyncAction;
	//这个AsyncAction对象就是this;
}

void UDtBlueprintHttpRequest::Activate()
{
	Super::Activate();
	// 这里不能睡 阻塞主线程
	M_HttpRequestInfo = NewObject<UDtHttpRequestInfo>(M_WorldContextObject);
	
	M_HttpRequestInfo->SenHttpRequest(M_RequestData);
}

void UDtBlueprintHttpRequest::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response,bool bWasSuccessful)
{
	UVaRestJsonObject* tempJson = NewObject<UVaRestJsonObject>();
	FString TemStr	= TEXT("nullptr");
	int temCode	= -1;

	if (bWasSuccessful)
	{
		TemStr	= Response->GetContentAsString();

		temCode	= Response->GetResponseCode();
	}

	UE_LOG(LogTemp, Log, TEXT("这是第二个OnHttpRequestCompleted = %s"),*TemStr)

	tempJson->DecodeJson(TemStr, true);
	OnCompleted.Broadcast(tempJson,temCode,bWasSuccessful);
	SetReadyToDestroy();
}

UDtBlueprintHttpRequest::UDtBlueprintHttpRequest()
{
}

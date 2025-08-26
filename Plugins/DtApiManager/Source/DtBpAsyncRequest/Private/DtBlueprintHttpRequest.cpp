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

	M_HttpRequestInfo = NewObject<UDtHttpRequestInfo>(M_WorldContextObject);
	
	M_HttpRequestInfo->SenHttpRequest(M_RequestData);
}

void UDtBlueprintHttpRequest::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response,bool bWasSuccessful)
{
	UVaRestJsonObject* tempJson = NewObject<UVaRestJsonObject>();
	UE_LOG(LogTemp, Log, TEXT("这是第二个OnHttpRequestCompleted = %s"),*Response->GetContentAsString())
	tempJson->DecodeJson(Response->GetContentAsString(), true);
	OnCompleted.Broadcast(tempJson,Response->GetResponseCode(),bWasSuccessful);
	SetReadyToDestroy();
}

UDtBlueprintHttpRequest::UDtBlueprintHttpRequest()
{
}

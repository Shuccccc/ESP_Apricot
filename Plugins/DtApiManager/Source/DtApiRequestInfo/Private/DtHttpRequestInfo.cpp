// Fill out your copyright notice in the Description page of Project Settings.


#include "DtHttpRequestInfo.h"
#include "DtApiManagerSubsystem.h"
#include "HTTP.h"

void UDtHttpRequestInfo::SenHttpRequest(RequestDataObject& RequestDataObject)
{
	bool bSucces = false;
	M_RequestDataObject = RequestDataObject;
	
//	UDtApiManagerSubsystem* DtApiManagerSubsystem = CastChecked<UDtApiManagerSubsystem>(USubsystemBlueprintLibrary::GetEngineSubsystem(UDtApiManagerSubsystem::StaticClass()));
	auto* GameWorld= GetOuter()->GetWorld();

	if (! GameWorld)
	{
		RequestDataObject.CallBack.ExecuteIfBound(FHttpRequestPtr{}, FHttpResponsePtr{}, false );
		return;
	}
	UDtApiManagerSubsystem* DtApiManagerSubsystem = GameWorld->GetGameInstance()->GetSubsystem<UDtApiManagerSubsystem>();
	
	if (! DtApiManagerSubsystem)
	{
		RequestDataObject.CallBack.ExecuteIfBound(FHttpRequestPtr{}, FHttpResponsePtr{}, false );
		return;
	}
	
	FString RequestUrl = DtApiManagerSubsystem->GetApiUrlForKey(RequestDataObject , bSucces);
	
	DtApiManagerSubsystem->GetHeaderForKey(RequestDataObject, bSucces);
	if (!bSucces)
	{
		RequestDataObject.CallBack.ExecuteIfBound(FHttpRequestPtr{}, FHttpResponsePtr{}, false );
	}
	


	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(RequestUrl);
	DtApiManagerSubsystem->AppendContentType(RequestDataObject);

	for (auto Header : RequestDataObject.HeaderParams)
	{
		Request->AppendToHeader(Header.Key, Header.Value);
	}
	Request->SetVerb(DtApiManagerSubsystem->GetVerbForKey(RequestDataObject));

	Request->SetContentAsString(DtApiManagerSubsystem->GetContent(RequestDataObject));
	Request->OnProcessRequestComplete().BindUObject(this, &UDtHttpRequestInfo::OnHttpRequestCompleted);
	

	UE_LOG(LogTemp, Log, TEXT("这是第一个RequestUrl = %s"),*RequestUrl)

	FString TemLogStr;
	for (TPair<FString, FString> HeaderParam : RequestDataObject.HeaderParams)
	{
		TemLogStr.Append(HeaderParam.Key + ":" + HeaderParam.Value + ",");
	}
	UE_LOG(LogTemp, Log, TEXT("这是第一个HeaderParams = %s"),*TemLogStr)

	UE_LOG(LogTemp, Log, TEXT("这是第一个Content = %s"),* DtApiManagerSubsystem->GetContent(RequestDataObject))
	
	Request->ProcessRequest();
	
}

void UDtHttpRequestInfo::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	M_RequestDataObject.CallBack.ExecuteIfBound(Request, Response, bWasSuccessful);
	FPlatformTypeLayoutParameters LayoutParameters;
	FMemoryToStringContext ToStringContext;
	Request->GetAllHeaders().ToString(LayoutParameters,ToStringContext);
	UE_LOG(LogTemp, Log, TEXT("这是第一个OnHttpRequestCompleted = %p"),ToStringContext.String)
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "DtWebBrowser.h"

#include "AudioMixerBlueprintLibrary.h"
#include "SWebBrowser.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#if WITH_EDITOR
#endif

#define LOCTEXT_NAMESPACE "WebBrowser"

/////////////////////////////////////////////////////
// UWebBrowser

UDtWebBrowser::UDtWebBrowser(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;
}

void UDtWebBrowser::LoadURL(FString NewURL)
{
	if ( WebBrowserWidget.IsValid() )
	{
		return WebBrowserWidget->LoadURL(NewURL);
	}
}

void UDtWebBrowser::LoadString(FString Contents, FString DummyURL)
{
	if ( WebBrowserWidget.IsValid() )
	{
		return WebBrowserWidget->LoadString(Contents, DummyURL);
	}
}

void UDtWebBrowser::ExecuteJavascript(const FString& ScriptText)
{
	if (WebBrowserWidget.IsValid())
	{
		return WebBrowserWidget->ExecuteJavascript(ScriptText);
	}
}

FText UDtWebBrowser::GetTitleText() const
{
	if ( WebBrowserWidget.IsValid() )
	{
		return WebBrowserWidget->GetTitleText();
	}

	return FText::GetEmpty();
}

FString UDtWebBrowser::GetUrl() const
{
	if (WebBrowserWidget.IsValid())
	{
		return WebBrowserWidget->GetUrl();
	}

	return FString();
}

void UDtWebBrowser::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	WebBrowserWidget.Reset();
}

TSharedRef<SWidget> UDtWebBrowser::RebuildWidget()
{
	if ( IsDesignTime() )
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Web Browser", "Web Browser"))
			];
	}
	else
	{
		WebBrowserWidget = SNew(SWebBrowser)
			.InitialURL(InitialURL)
			.ShowControls(false)
			.SupportsTransparency(bSupportsTransparency)
			.OnUrlChanged(BIND_UOBJECT_DELEGATE(FOnTextChanged, HandleOnUrlChanged))
			.OnBeforePopup(BIND_UOBJECT_DELEGATE(FOnBeforePopupDelegate, HandleOnBeforePopup))
			.OnConsoleMessage(BIND_UOBJECT_DELEGATE(FOnConsoleMessageDelegate, HandleOnConsoleMessage))
			.OnLoadCompleted(BIND_UOBJECT_DELEGATE(FSimpleDelegate , HandleOnLoadCompleted));

		return WebBrowserWidget.ToSharedRef();
	}
}

void UDtWebBrowser::BindObject(FString Name, UObject* Object)
{
	WebBrowserWidget->BindUObject(Name, Object);
}

void UDtWebBrowser::UnBindObject(FString Name, UObject* Object)
{
	WebBrowserWidget->UnbindUObject(Name,Object);
}

void UDtWebBrowser::EnableIME()
{
	if (WebBrowserWidget.IsValid())
		WebBrowserWidget->BindInputMethodSystem(FSlateApplication::Get().GetTextInputMethodSystem());
}

void UDtWebBrowser::HandleOnLoadCompleted()
{
	OnLoadCompleted.Broadcast();
}

void UDtWebBrowser::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if ( WebBrowserWidget.IsValid() )
	{

	}
}

void UDtWebBrowser::HandleOnUrlChanged(const FText& InText)
{
	OnUrlChanged.Broadcast(InText);
}

void UDtWebBrowser::HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity)
{
	OnConsoleMessage.Broadcast(Message, Source, Line);
}

bool UDtWebBrowser::HandleOnBeforePopup(FString URL, FString Frame)
{
	if (OnBeforePopup.IsBound())
	{
		if (IsInGameThread())
		{
			OnBeforePopup.Broadcast(URL, Frame);
		}
		else
		{
			// Retry on the GameThread.
			TWeakObjectPtr<UDtWebBrowser> WeakThis = this;
			FFunctionGraphTask::CreateAndDispatchWhenReady([WeakThis, URL, Frame]()
			{
				if (WeakThis.IsValid())
				{
					WeakThis->HandleOnBeforePopup(URL, Frame);
				}
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		}

		return true;
	}

	return false;
}

#if WITH_EDITOR

const FText UDtWebBrowser::GetPaletteCategory()
{
	return LOCTEXT("Experimental", "Experimental");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

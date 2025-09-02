// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/Widget.h"

#include "DtWebBrowser.generated.h"

enum class EWebBrowserConsoleLogSeverity;

/**
 * 
 */
UCLASS()
class DTWEBBROWSERWIDGET_API UDtWebBrowser : public UWidget
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUrlChanged, const FText&, Text);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeforePopup, FString, URL, FString, Frame);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConsoleMessage, const FString&, Message, const FString&, Source, int32, Line);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebBrowserLoadCompleted);



	UFUNCTION(BlueprintCallable, Category="Web Browser")
	void LoadURL(FString NewURL);

	/**
	 * Load a string as data to create a web page
	 *
	 * @param Contents String to load
	 * @param DummyURL Dummy URL for the page
	 */
	UFUNCTION(BlueprintCallable, Category="Web Browser")
	void LoadString(FString Contents, FString DummyURL);


	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void ExecuteJavascript(const FString& ScriptText);

	/**
	 * Get the current title of the web page
	 */
	UFUNCTION(BlueprintCallable, Category="Web Browser")
	FText GetTitleText() const;


	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	FString GetUrl() const;

	/** Called when the Url changes. */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnUrlChanged OnUrlChanged;

	/** Called when a popup is about to spawn. */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnBeforePopup OnBeforePopup;

	/** Called when the browser has console spew to print */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnConsoleMessage OnConsoleMessage;

	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void BindObject (FString Name, UObject* Object );
	
	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void UnBindObject(FString Name , UObject* Object );

	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void EnableIME();
	

	UPROPERTY(BlueprintAssignable, Category = "WebBrowser")
	FWebBrowserLoadCompleted OnLoadCompleted;

	void HandleOnLoadCompleted ();
	
public:
	
	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	// End UWidget interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	/** URL that the browser will initially navigate to. The URL should include the protocol, eg http:// */
	UPROPERTY(EditAnywhere, Category=Appearance)
	FString InitialURL;

	/** Should the browser window support transparency. */
	UPROPERTY(EditAnywhere, Category=Appearance)
	bool bSupportsTransparency;

protected:
	TSharedPtr<class SWebBrowser> WebBrowserWidget;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	void HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity);
	void HandleOnUrlChanged(const FText& Text);
	bool HandleOnBeforePopup(FString URL, FString Frame);
};

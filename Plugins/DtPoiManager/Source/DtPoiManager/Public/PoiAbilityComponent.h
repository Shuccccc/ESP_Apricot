// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoiAbilityComponent.generated.h"

class ADtPoiActorBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWidgetClickedDelegate, ADtPoiActorBase*,POIActor, FString,data);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DTPOIMANAGER_API UPoiAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPoiAbilityComponent();

	UFUNCTION(BlueprintCallable , Category = "PoiComponent",Meta = (DeterminesOutputType = "PoiClass"))
	ADtPoiActorBase* GetPoiActor(TSubclassOf<ADtPoiActorBase> PoiClass,FString PoiID);
	
	UFUNCTION(BlueprintCallable , Category = "PoiComponent")
	void ReleasesPoi(ADtPoiActorBase *PoiActor);

	UFUNCTION(BlueprintCallable , Category = "PoiComponent")
	void SetPoiVisibility(ADtPoiActorBase *PoiActor,bool bHide);

	UFUNCTION(BlueprintCallable , Category = "PoiComponent")
	void ReleasesAllPoi();

	UFUNCTION(BlueprintCallable , Category = "PoiComponent")
	ADtPoiActorBase* GetPoiActorById(FString PoiID) const;

	UPROPERTY(BlueprintAssignable , Category = "PoiDelegate")
	FWidgetClickedDelegate OnWidgetClicked_B;

	UPROPERTY(BlueprintAssignable , Category = "PoiDelegate")
	FWidgetClickedDelegate OnWidgetClicked_C;

	UPROPERTY(BlueprintAssignable , Category = "PoiDelegate")
	FWidgetClickedDelegate OnWidgetClicked_D;
	
private:
	
	UPROPERTY()
	TMap<FString , ADtPoiActorBase*> PoiActorMap;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

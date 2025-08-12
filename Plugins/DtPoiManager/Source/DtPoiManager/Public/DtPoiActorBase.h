// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalSearchInterface.h"
#include "GameFramework/Actor.h"
#include "DtPoiActorBase.generated.h"

class UWidgetComponent;

UCLASS()
class DTPOIMANAGER_API ADtPoiActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADtPoiActorBase();
	
	UPROPERTY(BlueprintReadWrite)
	UWidgetComponent* PoiWidget;

	UPROPERTY(BlueprintReadWrite)
	UChildActorComponent* MountActor;
//设置Widget
	UFUNCTION(BlueprintCallable , Category = "SetPoiWidget")
	ADtPoiActorBase* SetWidget(UUserWidget *Widget);
	
	UFUNCTION(BlueprintCallable , Category = "SetPoiWidget")
	ADtPoiActorBase* SetPivot(FVector2D Pivot);
	
	UFUNCTION(BlueprintCallable , Category = "PoiComponent")
	ADtPoiActorBase* GetPoiActorById(FString PoiID) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

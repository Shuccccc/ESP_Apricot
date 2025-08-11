// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalSearchInterface.h"
#include "GameFramework/Actor.h"
#include "DtPoiActor.generated.h"

class UWidgetComponent;

UCLASS()
class DTPOIMANAGER_API ADtPoiActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADtPoiActor();
	
	UPROPERTY(BlueprintReadWrite)
	UWidgetComponent* PoiWidget;

	UPROPERTY(BlueprintReadWrite)
	UChildActorComponent* MountActor;
//设置Widget
	UFUNCTION(BlueprintCallable , Category = "SetPoiWidget")
	ADtPoiActor* SetWidget(UUserWidget *Widget);
	
	UFUNCTION(BlueprintCallable , Category = "SetPoiWidget")
	ADtPoiActor* SetPivot(FVector2D Pivot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

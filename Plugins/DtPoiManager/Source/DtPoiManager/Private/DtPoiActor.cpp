// Fill out your copyright notice in the Description page of Project Settings.


#include "DtPoiActor.h"

#include "GlobalSearchSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/ChildActorComponent.h"


// Sets default values
ADtPoiActor::ADtPoiActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PoiWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PoiWidget"));
	MountActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("SubActor"));
}

ADtPoiActor* ADtPoiActor::SetWidget(UUserWidget* Widget)
{
	PoiWidget->SetWidget(Widget);
	return this;
}

ADtPoiActor* ADtPoiActor::SetPivot(FVector2D Pivot)
{
	PoiWidget->SetPivot(Pivot);
	return this;
}


// Called when the game starts or when spawned
void ADtPoiActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADtPoiActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "DtPoiActorBase.h"

#include "GlobalSearchSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/ChildActorComponent.h"


// Sets default values
ADtPoiActorBase::ADtPoiActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PoiWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PoiWidget"));
	MountActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("SubActor"));
}

ADtPoiActorBase* ADtPoiActorBase::SetPivot(FVector2D Pivot)
{
	PoiWidget->SetPivot(Pivot);
	return this;
}


// Called when the game starts or when spawned
void ADtPoiActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADtPoiActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "PoiAbilityComponent.h"
#include "DtPoiActor.h"

// Sets default values for this component's properties
UPoiAbilityComponent::UPoiAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ADtPoiActor* UPoiAbilityComponent::GetPoiActor(FString PoiID)
{
	
	return nullptr;
}

void UPoiAbilityComponent::ReleasesPoi(ADtPoiActor* PoiActor)
{
	for (auto i :PoiActor->Children)
	{
		i->Destroy();
	}
	PoiActor->Destroy();
	
}

void UPoiAbilityComponent::SetPoiVisibility(bool bHide)
{
	
}


// Called when the game starts
void UPoiAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPoiAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


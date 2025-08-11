// Fill out your copyright notice in the Description page of Project Settings.


#include "PoiAbilityComponent.h"
#include "DtPoiActor.h"
#include "Components/WidgetComponent.h"

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
	PoiActor->PoiWidget->GetWidget()->RemoveFromParent();
	PoiActor->Destroy();
}

void UPoiAbilityComponent::SetPoiVisibility(ADtPoiActor* PoiActor,bool bHide)
{
	PoiActor->SetActorHiddenInGame(!bHide);
	for (auto i : PoiActor->GetComponents())
	{
		if (USceneComponent* SceneComponent = Cast<USceneComponent>(i))
		{
			SceneComponent->SetHiddenInGame(!bHide);
		}
	}
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


// Fill out your copyright notice in the Description page of Project Settings.


#include "PoiAbilityComponent.h"
#include "DtPoiActorBase.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UPoiAbilityComponent::UPoiAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ADtPoiActorBase* UPoiAbilityComponent::GetPoiActor(TSubclassOf<ADtPoiActorBase> PoiClass,FString PoiID)
{
	//生成actor
	auto i= GetWorld()->SpawnActor<ADtPoiActorBase>(PoiClass);
	
	PoiActorMap.Add(PoiID,i);
	
	return i ;
}
ADtPoiActorBase* UPoiAbilityComponent::GetPoiActorById(FString PoiID) const
{
	return PoiActorMap.FindRef(PoiID);
}
void UPoiAbilityComponent::ReleasesPoi(ADtPoiActorBase* PoiActor)
{
	PoiActor->PoiWidget->GetWidget()->RemoveFromParent();
	PoiActor->Destroy();
}

void UPoiAbilityComponent::SetPoiVisibility(ADtPoiActorBase* PoiActor,bool bHide)
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

void UPoiAbilityComponent::ReleasesAllPoi()
{
	for (auto i : PoiActorMap)
	{
		ReleasesPoi(i.Value);
	}
	PoiActorMap.Empty();
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


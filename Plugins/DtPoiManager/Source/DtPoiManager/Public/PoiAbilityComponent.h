// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoiAbilityComponent.generated.h"

class ADtPoiActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DTPOIMANAGER_API UPoiAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPoiAbilityComponent();

	UFUNCTION(BlueprintCallable , Category = "Poi")
	ADtPoiActor* GetPoiActor(FString PoiID);
	
	UFUNCTION(BlueprintCallable , Category = "Poi")
	void ReleasesPoi(ADtPoiActor *PoiActor);

	UFUNCTION(BlueprintCallable , Category = "Poi")
	void SetPoiVisibility(bool bHide);

	
private:
	
	UPROPERTY()
	TMap<FString , ADtPoiActor*> PoiActorMap;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

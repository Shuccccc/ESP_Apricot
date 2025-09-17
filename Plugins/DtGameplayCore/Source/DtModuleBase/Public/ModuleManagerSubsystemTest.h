// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ModuleManagerSubsystemTest.generated.h"

/**
 * 
 */
class AModuleBaseActor;
UCLASS()
class DTMODULEBASE_API UModuleManagerSubsystemTest : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	virtual bool ShouldCreateSubsystem(UObject* Outer)  { return false; } 

	//virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable,Meta = (DeterminesOutputType = "ModuleClass"))
	AModuleBaseActor* GetModuleFromClass(TSubclassOf<AModuleBaseActor> ModuleClass);
private:

	void AsyncLoadCompleted();

	UPROPERTY()
	TArray<AModuleBaseActor*> ModuleList;
};

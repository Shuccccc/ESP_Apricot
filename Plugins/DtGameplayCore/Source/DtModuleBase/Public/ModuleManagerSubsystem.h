// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModuleBaseActor.h"
#include "ModuleManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DTMODULEBASE_API UModuleManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
 
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	TArray<AModuleBaseActor*> InitModuleSubsystem();
	
	UFUNCTION(BlueprintCallable,Meta = (DeterminesOutputType = "ModuleClass"))
	AModuleBaseActor* GetModule(TSubclassOf<AModuleBaseActor> ModuleClass);
private:
	UPROPERTY()
	TArray<AModuleBaseActor*> ModuleActors;

	void ForceLoadBlueprints();
};

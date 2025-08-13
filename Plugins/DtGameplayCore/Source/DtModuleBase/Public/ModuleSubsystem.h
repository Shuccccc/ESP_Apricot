// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModuleBaseActor.h"
#include "ModuleSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DTMODULEBASE_API UModuleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
 
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	TArray<AModuleBaseActor*> InitModuleSubsystem();
	
	UFUNCTION(BlueprintCallable,Meta = (DeterminesOutputType = "ModuleClass"))
	AModuleBaseActor* GetModule(TSubclassOf<AModuleBaseActor> ModuleClass);
private:
	UPROPERTY()
	TArray<AModuleBaseActor*> ModuleActors;

	void ForceLoadBlueprints();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtModuleManagerSubsystem.generated.h"

/**
 * 
 */

class ADtModuleBase ;
class UDtModuleToolBase;
UCLASS()
class DTMODULEMANAGER_API UDtModuleManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void OnWorldLoaded(UWorld* NewWorld);
	void LoadModules();


	UFUNCTION(BlueprintCallable , Category = "ModuleManager",meta=(DeterminesOutputType = "ModuleClass"))
	TSubclassOf<ADtModuleBase> GetModuleFromClass(TSubclassOf<ADtModuleBase> ModuleClass);
	

private:


	TArray<TWeakObjectPtr<UDtModuleToolBase>> CoreModules;

	TArray<TWeakObjectPtr<ADtModuleBase>> M_Modules; 	
	void OnAllModulesLoaded();
	
	FDelegateHandle OnWorldLoadedDelegateHandle;
	
	

};

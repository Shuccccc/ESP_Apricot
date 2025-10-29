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

	void LoadModules();



private:

	void OnAllModulesLoaded();

	
	TArray<TWeakObjectPtr<UDtModuleToolBase>> CoreModules;

	TArray<TWeakObjectPtr<ADtModuleBase>> Modules; 
};

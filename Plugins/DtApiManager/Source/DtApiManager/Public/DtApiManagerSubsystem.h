// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DtApiManagerSubsystem.generated.h"

/**
 * 
 */


UCLASS()
class DTAPIMANAGER_API UDtApiManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
 
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

//Blueprint

	UFUNCTION(BlueprintCallable, Category = "DtApiManager")
	void InitApiManager(UDataTable *ApiConfigTable);
	


private:
	UPROPERTY()
	TMap<FString, FString> ConfigMap;

	bool InitDefaultPlatform();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DtModuleBase.generated.h"


/*
 * ModuleActor默认关闭Tick  
 */
UCLASS(Abstract)
class DTMODULEMANAGER_API ADtModuleBase : public AActor
{
	GENERATED_BODY()

public:

	//实现此方法才能在ModuleManager中生成
	UFUNCTION( BlueprintCallable ,BlueprintNativeEvent)
	void ResetToDefault();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	ADtModuleBase();
};

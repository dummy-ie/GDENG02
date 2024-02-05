// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "SpawnInput.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USpawnInput : public UInputComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	USpawnInput();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

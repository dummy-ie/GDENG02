// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ControllerSwitcher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNOWMAN_API UControllerSwitcher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UControllerSwitcher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	const FName SWITCH = FName("Switch");

	UPROPERTY(EditAnywhere)
	TArray<APawn*> snowmen;

	AController *controller = NULL; 
	int currentSnowman = 0;

	void SwitchSnowman();

	// UPROPERTY(EditAnywhere)
	// AActor* snowman1 = NULL;

	// UPROPERTY(EditAnywhere)
	// AActor* snowman2 = NULL;
	
	// UPROPERTY(EditAnywhere)
	// AActor* snowman3 = NULL;
};

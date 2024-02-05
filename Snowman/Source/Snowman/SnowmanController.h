// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SnowmanController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNOWMAN_API USnowmanController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USnowmanController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	const FName MOVE_X_KEY = FName("MoveX");
	const FName MOVE_Y_KEY = FName("MoveY");

	UPROPERTY(EditAnywhere) APawn* snowmanPawn;
	UPROPERTY(EditAnywhere) float SPEED_MULTIPLIER = 300.0f;

	void MoveX(float axisValue);
	void MoveY(float axisValue);

	float movementX = 0.0f;
	float movementY = 0.0f;
	bool alongX = false;
	bool alongY = false;
};

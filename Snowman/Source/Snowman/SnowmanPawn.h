// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnowmanPawn.generated.h"

UCLASS()
class SNOWMAN_API ASnowmanPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnowmanPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere) USceneComponent* sceneComponent;
	// UPROPERTY(EditAnywhere) APawn* snowmanPawn;
	UPROPERTY(EditAnywhere) float SPEED_MULTIPLIER = 300.0f;
	
	const FName MOVE_X_KEY = FName("MoveX");
	const FName MOVE_Y_KEY = FName("MoveY");

	void MoveX(float axisValue);
	void MoveY(float axisValue);

	float movementX = 0.0f;
	float movementY = 0.0f;
	bool alongX = false;
	bool alongY = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/InputComponent.h"	
#include "CPP_Panel.generated.h"

UCLASS()
class MYPROJECT_API ACPP_Panel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Panel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PanelMesh;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float MaxDistance;

	UPROPERTY(EditAnywhere)
	float InterpSpeed;

private:
	FVector InitialLocation;
	FVector TargetLocation;
	int speedMultiplier = 1;

	UPROPERTY()
	UPhysicsConstraintComponent* PhysicsConstraintComponent;
	
	void IncreaseSpeed();
	void DecreaseSpeed();
};

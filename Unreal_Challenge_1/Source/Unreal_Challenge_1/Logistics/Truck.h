// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Components/InterpToMovementComponent.h"
#include "Containers/Map.h"
#include "Containers/Queue.h"
#include "Algo/Reverse.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/TriggerVolume.h"
#include "../Buildings/ProductionBuilding.h"
#include "../GameManager.h"
#include "Truck.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class UNREAL_CHALLENGE_1_API ATruck : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ATruck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// overlap begin function
	UFUNCTION()
	void OnBeginTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Truck")
	ResourceType GetCargoType();

	UFUNCTION(BlueprintCallable, Category = "Truck")
	int GetCargoCount();

private:
	void ReturnToNeutralState();
	void ProcessBuildingRequest();
	
	void InterpTo(FVector destination);
	TArray<FVector> FindPath(FVector closestAnchor, FVector destinationAnchor);

	UPROPERTY(EditAnywhere) // check in editor
	bool isTransporting = false;

	UPROPERTY(EditAnywhere)
	TArray<ResourceType> cargo;

	UPROPERTY(EditAnywhere)
	int cargoCapacity = 2;

	int numItemsToTake;
	int buildingCurrentCount;

	UPROPERTY(EditAnywhere)
	UInterpToMovementComponent *interp;
	
	UPROPERTY(EditAnywhere)
	AGameManager* gameManager;

	UPROPERTY(EditAnywhere) // check in editor
	FDeliveryRequest currentDelivery;

	UPROPERTY(EditAnywhere) // check in editor
	UProductionBuilding* overlappedBuilding;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* trigger;

	TMap<FVector, TArray<FVector>> adjacentMap;
};

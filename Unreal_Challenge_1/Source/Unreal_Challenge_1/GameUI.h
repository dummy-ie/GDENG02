// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
// #include "Buildings/ProductionBuilding.h"
#include "GameUI.generated.h"

class UProductionBuilding;

/**
 *
 */
UCLASS(Blueprintable)
class UNREAL_CHALLENGE_1_API UGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// UPROPERTY(BlueprintNativeEvent)
	// float GetProductionProgress(const UProductionBuilding& building);

	// UPROPERTY(BlueprintNativeEvent)
	// TMap<ResourceType, int> GetInputCounts(const UProductionBuilding& building);

	// UPROPERTY(BlueprintNativeEvent)
	// int GetOutputCount(const UProductionBuilding& building);

	// UPROPERTY(BlueprintNativeEvent)
	// ResourceType GetCargoType(const ATruck& truck);

	// UPROPERTY(BlueprintNativeEvent)
	// int GetCargoCount(const ATruck& truck);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UProductionBuilding*> buildings;

	UFUNCTION(BlueprintImplementableEvent)
	void SetBuildingValues(const TArray<AActor *> &buildingActors);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTruckValues(const TArray<ATruck *> &trucks);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Enums/ResourceType.h"
#include "../Enums/RequestType.h"
#include "../GameManager.h"
#include "ProductionBuilding.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class UNREAL_CHALLENGE_1_API UProductionBuilding : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProductionBuilding();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	TArray<ResourceType> takeOutput(int numItems);
	TArray<ResourceType> takeOutput(int numItems, ResourceType resource);
	void addInput(TArray<ResourceType> input);
	int GetNeededResourceCount(ResourceType resource);
	TArray<ResourceType> GetNeededResources();
	TArray<ResourceType> GetInputTypes();
	ResourceType GetOutputType();
	int GetPerResourceLimit();

	UFUNCTION(BlueprintCallable, Category = "Production")
	const FString GetName();
	
	UFUNCTION(BlueprintCallable, Category = "Production")
	float GetProductionProgress();

	UFUNCTION(BlueprintCallable, Category = "Production")
	TMap<ResourceType, int> GetInputCounts();
	
	UFUNCTION(BlueprintCallable, Category = "Production")
	int GetOutputCount();

	bool HasOutput();
	bool hasInput();

	UPROPERTY(EditAnywhere)
	AActor *transportAnchorPoint;


private:
	UPROPERTY(EditAnywhere)
	FString name;

	UPROPERTY(EditAnywhere)
	bool limitOutput = true;

	UPROPERTY(EditAnywhere)
	int perResourceLimit = 3;

	UPROPERTY(EditAnywhere)
	TArray<ResourceType> inputType;

	UPROPERTY(EditAnywhere)
	ResourceType outputType;

	UPROPERTY(EditAnywhere)
	float productionTime;

	float productionClock = 0;
	float requestClock = 0;

	bool canProduce = true;

	UPROPERTY(EditAnywhere)
	AGameManager *gameManager;

	TArray<ResourceType> input;

	TArray<ResourceType> output;

	UProductionBuilding *FindBuildingNeedsResource(ResourceType resource);
	UProductionBuilding *FindBuildingWithResource(ResourceType resource);
	int countResource(ResourceType type, TArray<ResourceType> array);
	void addOutput();
};

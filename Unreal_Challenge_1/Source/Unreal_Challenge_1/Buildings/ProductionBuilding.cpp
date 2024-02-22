// Fill out your copyright notice in the Description page of Project Settings.

#include "ProductionBuilding.h"

// Sets default values for this component's properties
UProductionBuilding::UProductionBuilding()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UProductionBuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UProductionBuilding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (hasInput() && (output.Num() < perResourceLimit || !limitOutput))
	{
		canProduce = true;
	}
	else
	{
		requestClock += DeltaTime;
		canProduce = false;
		productionClock = 0;
	}

	if (canProduce)
		productionClock += DeltaTime;

	if (productionClock >= productionTime)
	{
		if (hasInput() && (output.Num() < perResourceLimit || !limitOutput))
			addOutput();
		else
			canProduce = false;

		productionClock = 0;
	}

	if (requestClock >= 5)
	{
		for (auto resource : GetNeededResources())
		{
			FDeliveryRequest newRequest = FDeliveryRequest(resource, FindBuildingWithResource(resource), this, 1);
			gameManager->CreateRequest(newRequest);
		}
		requestClock = 0;
	}
}

UProductionBuilding *UProductionBuilding::FindBuildingNeedsResource(ResourceType resource)
{
	if (!gameManager)
		return nullptr;

	TArray<UProductionBuilding *> buildings = TArray<UProductionBuilding *>();
	for (auto actor : gameManager->buildingActors)
	{
		UProductionBuilding *comp = actor->GetComponentByClass<UProductionBuilding>();
		buildings.Add(comp);
	}

	for (auto building : buildings)
	{
		for (auto needs : building->GetNeededResources())
		{
			if (needs == resource && !building->hasInput())
			{
				return building;
			}
		}
	}

	return nullptr;
}

UProductionBuilding *UProductionBuilding::FindBuildingWithResource(ResourceType resource)
{
	if (!gameManager)
		return nullptr;

	TArray<UProductionBuilding *> buildings = TArray<UProductionBuilding *>();
	for (auto actor : gameManager->buildingActors)
	{
		UProductionBuilding *comp = actor->GetComponentByClass<UProductionBuilding>();
		buildings.Add(comp);
	}

	for (auto building : buildings)
	{
		if (building->GetOutputType() == resource && building->HasOutput())
		{
			return building;
		}
	}

	return nullptr;
}

TArray<ResourceType> UProductionBuilding::takeOutput(int numItems)
{
	TArray<ResourceType> resources = TArray<ResourceType>();

	for (size_t i = 0; i < numItems && i < output.Num(); i++)
	{
		resources.Add(output[i]);
	}

	return resources;
}

TArray<ResourceType> UProductionBuilding::takeOutput(int numItems, ResourceType resource)
{
	TArray<ResourceType> resources = TArray<ResourceType>();
	TArray<int32> indexes = TArray<int32>();

	for (size_t i = 0; i < numItems && i < output.Num(); i++)
	{
		if (output[i] == resource)
		{
			resources.Add(output[i]);
			indexes.Add(i);
		}
	}

	for(auto i : indexes)
	{
		if (i >= 0 && i < output.Num())
			output.RemoveAt(i);
	}

	return resources;
}

void UProductionBuilding::addInput(TArray<ResourceType> inputCargo)
{
	for (auto resource : inputCargo)
	{
		if (countResource(resource, input) < perResourceLimit)
		{
			input.Add(resource);
		}
	}
}

int UProductionBuilding::GetNeededResourceCount(ResourceType resource)
{
	return countResource(resource, input);
}

TArray<ResourceType> UProductionBuilding::GetNeededResources()
{
	TArray<ResourceType> needed = TArray<ResourceType>();

	for (auto resource : inputType)
	{
		if (countResource(resource, inputType) < perResourceLimit)
			needed.Add(resource);
	}

	for(auto var : needed)
	{
		UE_LOG(LogTemp, Display, TEXT("%s: Needs resources: %s"), *GetName(), *UEnum::GetValueAsString<ResourceType>(var));
	}
	return needed;
}

TArray<ResourceType> UProductionBuilding::GetInputTypes()
{
	return inputType;
}

ResourceType UProductionBuilding::GetOutputType()
{
	return outputType;
}

int UProductionBuilding::GetPerResourceLimit()
{
	return perResourceLimit;
}

const FString UProductionBuilding::GetName()
{
    return name;
}

float UProductionBuilding::GetProductionProgress()
{
    return productionClock / productionTime;
}

TMap<ResourceType, int> UProductionBuilding::GetInputCounts()
{
	TMap<ResourceType, int> counts;
	for (auto var : input)
	{
		counts.FindOrAdd(var)++;
	}
    return counts;
}

int UProductionBuilding::GetOutputCount()
{
    return output.Num();
}

bool UProductionBuilding::HasOutput()
{
	return countResource(outputType, output) > 0;
}

int UProductionBuilding::countResource(ResourceType type, TArray<ResourceType> array)
{
	int count = 0;
	for (auto resource : array)
	{
		if (resource == type)
			count++;
	}

	return count;
}

bool UProductionBuilding::hasInput()
{
	bool result = false;

	if (inputType.Num() == 0)
		result = true;
	else
	{
		for (auto type : inputType)
		{
			result = countResource(type, input) > 0;
			if (!result)
				return result;
		}
	}

	return result;
}

void UProductionBuilding::addOutput()
{
	UE_LOG(LogTemp, Display, TEXT("%s: Starting to add output"), *GetName());
	if (!hasInput())
		return;

	ResourceType newOutput = outputType;
	TArray<int32> indexes = TArray<int32>();
	if (inputType.Num() != 0)
	{
		for (auto type : inputType)
		{
			UE_LOG(LogTemp, Display, TEXT("%s: Finding input types"), *GetName());
			indexes.Add(input.Find(type));
		}

		for (auto index : indexes)
		{
			UE_LOG(LogTemp, Display, TEXT("%s: Removing from input with indexes"), *GetName());
			if (index >= 0 && index < input.Num())
				input.RemoveAt(index);
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: Input has no such index %d!"), *GetName(), index);
				return;
			}
		}
	}

	if (!gameManager)
		return;

	FDeliveryRequest newRequest = FDeliveryRequest(newOutput, this, FindBuildingNeedsResource(newOutput));
	gameManager->CreateRequest(newRequest);
	UE_LOG(LogTemp, Display, TEXT("%s: Adding to output"), *GetName());
	output.Add(newOutput);
}

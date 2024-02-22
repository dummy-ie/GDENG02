// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	// create widget and cast it to our UI
	if (gameWidgetClass)
	{
		gameWidget = Cast<UGameUI>(CreateWidget(GetWorld(), gameWidgetClass));

		if (gameWidget)
		{
			// now show the widget we created
			gameWidget->AddToViewport();
			gameWidget->SetBuildingValues(buildingActors);
		}
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gameWidget)
	{
		gameWidget->UpdateTruckValues(trucks);
	}
}

// void AGameManager::CreateRequest(TArray<ResourceType> neededResources, UProductionBuilding *source)
// {
// 	for (auto resource : neededResources)
// 	{
// 		FDeliveryRequest newRequest = FDeliveryRequest(resource, FindBuildingWithResource(resource), source);
// 		CreateRequest(newRequest);
// 	}
// }

void AGameManager::CreateRequest(FDeliveryRequest request)
{
	if (!request.buildingToDeliverTo || !request.buildingToTakeFrom)
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s: Request has null values!"), *GetName());
		return;
	} 

	// UE_LOG(LogTemp, Display, TEXT("%s: Submitting request."), *GetName());
	// requests.Enqueue(request);
	if (request.Priority < 0)
		SetRequestPriority(request);
	
	requests.HeapPush(request, FDeliveryRequestPredicate());
}

FDeliveryRequest AGameManager::AcceptRequest()
{
	FDeliveryRequest newRequest;
	if (!requests.IsEmpty())
	{
		// requests.Dequeue(newRequest);
		requests.HeapPop(newRequest, FDeliveryRequestPredicate());
		// UE_LOG(LogTemp, Display, TEXT("%s: Accepting request."), *GetName());
	}

	return newRequest;
}

void AGameManager::SetRequestPriority(FDeliveryRequest &request)
{
	switch (request.resourceToDeliver)
	{
	case ResourceType::STEEL_BEAM:
		request.Priority = 1;
		break;
	// case ResourceType::LUMBER:
	// 	request.Priority = 0;
	// 	break;
	
	default:
		request.Priority = 0;
		break;
	}
}

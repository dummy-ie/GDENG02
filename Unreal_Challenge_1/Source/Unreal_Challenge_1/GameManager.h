// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/RequestType.h"
#include "Enums/ResourceType.h"
// #include "Buildings/ProductionBuilding.h"
#include "Kismet/KismetArrayLibrary.h"
#include "GameUI.h"
#include "GameManager.generated.h"

class UProductionBuilding;
class UGameUI;
class ATruck;

USTRUCT(BlueprintType)
struct FDeliveryRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ResourceType resourceToDeliver;

	UPROPERTY(EditAnywhere)
	UProductionBuilding *buildingToDeliverTo;

	UPROPERTY(EditAnywhere)
	UProductionBuilding *buildingToTakeFrom;

	UPROPERTY(EditAnywhere)
	int32 Priority;

	FDeliveryRequest()
	{
		resourceToDeliver = ResourceType::NONE;
		buildingToDeliverTo = nullptr;
		buildingToTakeFrom = nullptr;
		Priority = -1;
	}

	// go to target, deliver to source
	FDeliveryRequest(ResourceType resource, UProductionBuilding *takeFrom, UProductionBuilding *deliverTo, int32 Prio = -1)
	{
		resourceToDeliver = resource;
		buildingToTakeFrom = takeFrom;
		buildingToDeliverTo = deliverTo;
		Priority = Prio;
	}

};

struct FDeliveryRequestPredicate
{
    bool operator()(const FDeliveryRequest& A, const FDeliveryRequest& B) const
    {
        // Inverted compared to std::priority_queue - higher priorities float to the top
        return A.Priority > B.Priority;
    }
};

UCLASS()
class UNREAL_CHALLENGE_1_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<AActor *> buildingActors;
	
	UPROPERTY(EditAnywhere)
	TArray<ATruck *> trucks;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// void CreateRequest(TArray<ResourceType> neededResources, UProductionBuilding* source);
	void CreateRequest(FDeliveryRequest request);
	FDeliveryRequest AcceptRequest();

private:
	// TQueue<FDeliveryRequest> requests;
	UPROPERTY(EditAnywhere)
	TArray<FDeliveryRequest> requests;

	void SetRequestPriority(FDeliveryRequest& request);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> gameWidgetClass;

	UPROPERTY()
	UGameUI *gameWidget;
};

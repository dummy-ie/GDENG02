// Fill out your copyright notice in the Description page of Project Settings.

#include "Truck.h"

ATruck::ATruck()
{
    this->interp = (UInterpToMovementComponent *)CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("Interp To Movement"));
    this->SetMobility(EComponentMobility::Movable);
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATruck::BeginPlay()
{
    /*
    between furnace & lumber
    -100, 10000, 0

    between iron & coal
    -100, -10000, 0

    coal
    -9000, -10000, 0

    furnace
    9000, 10000, 0

    iron
    9000, -10000, 0

    lumber
    -9000, 10000, 0

    sewing machine
    -100, 0, 0
    */

    Super::BeginPlay();

    TArray<FVector> betweenIronAndCoal = TArray<FVector>();
    betweenIronAndCoal.Add(FVector(9000, -10000, 0));
    betweenIronAndCoal.Add(FVector(-9000, -10000, 0));
    betweenIronAndCoal.Add(FVector(-100, 0, 0));

    TArray<FVector> betweenFurnaceAndLumber = TArray<FVector>();
    betweenFurnaceAndLumber.Add(FVector(9000, 10000, 0));
    betweenFurnaceAndLumber.Add(FVector(-9000, 10000, 0));
    betweenFurnaceAndLumber.Add(FVector(-100, 0, 0));

    TArray<FVector> coal = TArray<FVector>();
    coal.Add(FVector(-100, -10000, 0));

    TArray<FVector> iron = TArray<FVector>();
    iron.Add(FVector(-100, -10000, 0));

    TArray<FVector> furnace = TArray<FVector>();
    furnace.Add(FVector(-100, 10000, 0));

    TArray<FVector> lumber = TArray<FVector>();
    lumber.Add(FVector(-100, 10000, 0));

    TArray<FVector> sewingMachine = TArray<FVector>();
    sewingMachine.Add(FVector(-100, -10000, 0));
    sewingMachine.Add(FVector(-100, 10000, 0));

    adjacentMap.Add(FVector(-100, -10000, 0), betweenIronAndCoal);
    adjacentMap.Add(FVector(-100, 10000, 0), betweenFurnaceAndLumber);
    adjacentMap.Add(FVector(-9000, -10000, 0), coal);
    adjacentMap.Add(FVector(9000, -10000, 0), iron);
    adjacentMap.Add(FVector(9000, 10000, 0), furnace);
    adjacentMap.Add(FVector(-9000, 10000, 0), lumber);
    adjacentMap.Add(FVector(-100, 0, 0), sewingMachine);

    if (trigger)
        trigger->OnActorBeginOverlap.AddDynamic(this, &ATruck::OnBeginTriggerOverlap);
}

void ATruck::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!isTransporting && gameManager)
    {
        currentDelivery = gameManager->AcceptRequest();

        if (!currentDelivery.buildingToDeliverTo || !currentDelivery.buildingToTakeFrom)
            return;

        isTransporting = true;
        
        numItemsToTake = cargoCapacity;
        buildingCurrentCount = currentDelivery.buildingToDeliverTo->GetNeededResourceCount(currentDelivery.resourceToDeliver);
        while (buildingCurrentCount + numItemsToTake > currentDelivery.buildingToDeliverTo->GetPerResourceLimit())
            numItemsToTake--;

        if (numItemsToTake <= 1)
        {
            isTransporting = false;
        }
        else
            InterpTo(currentDelivery.buildingToTakeFrom->transportAnchorPoint->GetActorLocation());

        // UE_LOG(LogTemp, Display, TEXT("%s: Interpolating to building."), *GetName());
    }

    if (isTransporting && overlappedBuilding && overlappedBuilding == currentDelivery.buildingToTakeFrom)
    {
        FTimerHandle UnusedHandle;
        GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATruck::ProcessBuildingRequest, FMath::RandRange(1, 3), false);
    }
}

void ATruck::OnBeginTriggerOverlap(AActor *OverlappedActor, AActor *OtherActor)
{
    UProductionBuilding *overlap = OtherActor->GetComponentByClass<UProductionBuilding>();

    if (!overlap)
        return;
    else
        overlappedBuilding = overlap;

    // UE_LOG(LogTemp, Warning, TEXT("Overlapped with an actor %s"), *OtherActor->GetName());

    if (overlappedBuilding == currentDelivery.buildingToTakeFrom || overlappedBuilding == currentDelivery.buildingToDeliverTo)
    {
        // UE_LOG(LogTemp, Warning, TEXT("Overlapped with a building"));
        FTimerHandle UnusedHandle;
        GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATruck::ProcessBuildingRequest, FMath::RandRange(1, 3), false);
    }
}

ResourceType ATruck::GetCargoType()
{
    if (cargo.IsEmpty())
        return ResourceType::NONE;
    else
        return cargo[0];
}

int ATruck::GetCargoCount()
{
    return cargo.Num();
}

void ATruck::ReturnToNeutralState()
{
    if (FVector::Dist(GetActorLocation(), FVector(-100, -10000, 0)) < FVector::Dist(GetActorLocation(), FVector(-100, 10000, 0)))
        InterpTo(FVector(-100, -10000, 0));
    else
        InterpTo(FVector(-100, 10000, 0));
    
    isTransporting = false;
}

void ATruck::ProcessBuildingRequest()
{
    if (!overlappedBuilding)
        return;

    // UE_LOG(LogTemp, Display, TEXT("%s: Processing request"), *GetName());

    if (overlappedBuilding == currentDelivery.buildingToDeliverTo)
    {
        interp->ResetControlPoints(); // stop moving

        // UE_LOG(LogTemp, Display, TEXT("%s: Delivering cargo"), *GetName());
        overlappedBuilding->addInput(cargo);
        cargo.Empty();
        isTransporting = false;
        // FTimerHandle UnusedHandle;
        // GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATruck::ReturnToNeutralState, FMath::RandRange(0, 3), false);
    }
    else if (cargo.IsEmpty() && overlappedBuilding == currentDelivery.buildingToTakeFrom)
    {
        // UE_LOG(LogTemp, Display, TEXT("Taking output"));
        
        if (numItemsToTake > 0)
        {
            cargo = overlappedBuilding->takeOutput(numItemsToTake, currentDelivery.resourceToDeliver);
            InterpTo(currentDelivery.buildingToDeliverTo->transportAnchorPoint->GetActorLocation());
        }
        else
            isTransporting = false;

        overlappedBuilding = nullptr;
    }
}

void ATruck::InterpTo(FVector destination)
{
    interp->ResetControlPoints();
    interp->Duration = FMath::RandRange(4, 4);

    FVector currentAnchor = FVector(0);
    FVector closestAnchor = FVector(INT_MAX, INT_MAX, INT_MAX);
    TArray<FVector> path = TArray<FVector>();

    // find the closest anchor
    for (auto anchor : adjacentMap)
    {
        currentAnchor = anchor.Key;
        if (FVector::Dist(currentAnchor, GetActorLocation()) < FVector::Dist(closestAnchor, GetActorLocation()))
        {
            closestAnchor = currentAnchor;
        }
    }

    path = FindPath(closestAnchor, destination);

    interp->AddControlPointPosition(GetActorLocation(), false);
    for (auto point : path)
    {
        interp->AddControlPointPosition(point, false);
    }
    interp->FinaliseControlPoints();
    interp->RestartMovement();
}

TArray<FVector> ATruck::FindPath(FVector closestAnchor, FVector destinationAnchor)
{
    UE_LOG(LogTemp, Display, TEXT("%s: finding path..."), *GetName());

    TQueue<FVector> queue = TQueue<FVector>();
    TMap<FVector, bool> visited = TMap<FVector, bool>();
    TMap<FVector, FVector> parent = TMap<FVector, FVector>();

    queue.Enqueue(closestAnchor);
    visited.Add(closestAnchor, true);
    while (!queue.IsEmpty())
    {
        FVector current = FVector();
        queue.Dequeue(current);

        if (current == destinationAnchor)
            break;

        if (!adjacentMap.Contains(current))
        {
            return TArray<FVector>();
        }

        for (auto anchor : adjacentMap[current])
        {
            if (!visited.Contains(anchor))
            {
                visited.Add(anchor, true);
                parent.Add(anchor, current);
                queue.Enqueue(anchor);
            }
        }
    }

    FVector tracer = destinationAnchor;
    TArray<FVector> path = TArray<FVector>();
    path.Add(tracer);

    while (tracer != closestAnchor)
    {
        if (!parent.Contains(tracer))
        {
            return TArray<FVector>();
        }

        tracer = parent[tracer];
        path.Add(tracer);
    }

    Algo::Reverse(path);

    return path;
}
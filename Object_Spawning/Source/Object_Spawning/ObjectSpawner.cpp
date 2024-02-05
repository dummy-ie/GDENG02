// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectSpawner.h"

// Sets default values for this component's properties
UObjectSpawner::UObjectSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	actorCopy->SetActorHiddenInGame(true);
}

// Called every frame
void UObjectSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	ticks += DeltaTime;
	destroyTicks += DeltaTime;

	if (ticks > INTERVAL)
	{
		ticks = 0.0f;
		if (actorCopy != NULL && spawnedObjects.Num() < spawnLimit)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Template = actorCopy;
			spawnParams.Owner = GetOwner();

			FVector spawnLocation = GetOwner()->GetActorLocation();
			FRotator spawnRotation = GetOwner()->GetActorRotation();

			AActor *myActor = GetWorld()->SpawnActor<AActor>(actorCopy->GetClass(), spawnParams);
			myActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
			myActor->SetActorHiddenInGame(false);
			myActor->SetActorLocation(spawnLocation);
			myActor->SetActorRotation(spawnRotation);

			spawnedObjects.Add(myActor);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Actor is null, will not spawn."));
		}
	}

	if (destroyTicks > DELETE_INTERVAL)
	{
		destroyTicks = 0.0f;
		DeleteAll();
	}
}

void UObjectSpawner::DeleteAll()
{
	// for (auto obj : spawnedObjects)
	// {
	// 	obj.Destroy();
	// }

	spawnedObjects.Empty();
}

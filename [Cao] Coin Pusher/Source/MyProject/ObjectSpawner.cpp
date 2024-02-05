// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	this->actorCopy->SetActorHiddenInGame(true);
	
}

// Called every frame
void AObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->ticks += DeltaTime;
	this->destroyTicks += DeltaTime;

	if (this->ticks > this->INTERVAL) {
		this->ticks = 0.0f;

		if (this->actorCopy != NULL && this->spawnedObjects.Num() < this->spawnLimit) {
			FActorSpawnParameters spawnParams;
			spawnParams.Template = this->actorCopy;
			spawnParams.Owner = this->GetOwner();

			FVector spawnLocation = this->GetOwner()->GetActorLocation();
			FRotator spawnRotation = this->GetOwner()->GetActorRotation();

			AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
			myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
			myActor->SetActorHiddenInGame(false);
			myActor->SetActorLocation(spawnLocation);
			myActor->SetActorRotation(spawnRotation);

			this->spawnedObjects.Add(myActor);
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Actor is null. Will not spawn"));
		}
	}

	if (this->destroyTicks > this->DELETE_INTERVAL) {
		this->destroyTicks = 0.0f;
		this->DeleteAll();
	}
}

void AObjectSpawner::DeleteAll()
{

}

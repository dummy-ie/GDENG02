// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ObjectPool.h"

// Sets default values for this component's properties
UCPP_ObjectPool::UCPP_ObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCPP_ObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->Initialize();
}

// Called every frame
void UCPP_ObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCPP_ObjectPool::Initialize()
{
	if (this->actorCopy == NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("Actor is null. Object pool not initialized."));
		return;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Template = this->actorCopy;
	spawnParams.Owner = this->GetOwner();

	const FTransform transform = this->actorCopy->GetActorTransform();
	for (int i = 0; i < this->maxPoolSize - 1; i++)
	{
		AActorPoolable *poolableObject = this->GetWorld()->SpawnActor<AActorPoolable>(this->actorCopy->GetClass(), spawnParams);
		poolableObject->SetIndex(i);
		poolableObject->OnInitialize();
		this->availableObjects.Push(poolableObject);
	}
}

bool UCPP_ObjectPool::HasObjectAvailable(int requestSize)
{
	return this->availableObjects.Num() > 0;
}

int UCPP_ObjectPool::GetMaxPoolSize() const
{
	return this->maxPoolSize;
}

AActorPoolable *UCPP_ObjectPool::RequestPoolable()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	// Check if enough time has passed since the last request
	// if (CurrentTime - this->LastRequestTime < 1.0f) // Adjust the cooldown period as needed
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Cannot request object. Cooldown period not expired."));
	// 	return nullptr;
	// }

	if (this->HasObjectAvailable(1))
	{
		UE_LOG(LogTemp, Warning, TEXT("Object requested from pool"));
		AActorPoolable *object = this->availableObjects.Pop();
		object->SetIndex(this->usedObjects.Num());
		this->usedObjects.Push(object);
		object->OnActivate();
		object->SetActorTransform(this->GetOwner()->GetActorTransform());

		// Update the last request time
		LastRequestTime = CurrentTime;

		return object;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No more available objects in the pool."));
		return NULL;
	}
}

TArray<AActorPoolable *> UCPP_ObjectPool::RequestPoolableBatch(int size)
{
	TArray<AActorPoolable *> objects;
	for (int i = 0; i < size && this->availableObjects.Num() > 0; i++)
	{
		objects.Push(this->RequestPoolable());
	}

	return objects;
}

void UCPP_ObjectPool::ReleasePoolable(AActorPoolable *poolableObject)
{
	UE_LOG(LogTemp, Warning, TEXT("Object released back to pool"));
	poolableObject->OnRelease();
	this->usedObjects.Remove(poolableObject);
	this->availableObjects.Push(poolableObject);
}

void UCPP_ObjectPool::ReleasePoolableBatch(TArray<AActorPoolable *> objectList)
{
	for (int i = 0; i < objectList.Num(); i++)
	{
		this->ReleasePoolable(objectList[i]);
	}
}

void UCPP_ObjectPool::ReleasePoolableBatch(int count)
{
	TArray<AActorPoolable *> objectList;
	for (int i = 0; i < count && this->availableObjects.Num() > 0; i++)
	{
		this->ReleasePoolable(objectList[i]);
	}
}

void UCPP_ObjectPool::BeginDestroy()
{
	Super::BeginDestroy();

	for (int i = 0; i < this->availableObjects.Num(); i++)
	{
		this->availableObjects[i]->Destroy();
	}

	for (int i = 0; i < this->usedObjects.Num(); i++)
	{
		this->usedObjects[i]->Destroy();
	}

	this->availableObjects.Empty();
	this->usedObjects.Empty();
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinObjectPool.h"

// Sets default values for this component's properties
UCoinObjectPool::UCoinObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCoinObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Initialize();
}

void UCoinObjectPool::BeginDestroy()
{
	Super::BeginDestroy();
	for (auto obj : availableObjects)
	{
		obj->Destroy();
	}

	for (auto obj : usedObjects)
	{
		obj->Destroy();
	}

	availableObjects.Empty();
	usedObjects.Empty();
}

// Called every frame
void UCoinObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoinObjectPool::Initialize()
{
	if (actorCopy == NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("Actor is null, Object pool uninitialized."));
		return;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Template = actorCopy;
	spawnParams.Owner = GetOwner();

	const FTransform transform = actorCopy->GetActorTransform();
	for (size_t i = 0; i < maxPoolSize - 1; i++)
	{
		AActorPoolable *poolableObject = GetWorld()->SpawnActor<AActorPoolable>(actorCopy->GetClass(), spawnParams);
		poolableObject->SetIndex(i);
		poolableObject->OnInitialize();
		availableObjects.Push(poolableObject);
	}
}

bool UCoinObjectPool::HasObjectAvailable(int requestSize)
{
	return availableObjects.Num() > 0;
}

int UCoinObjectPool::GetMaxPoolSize()
{
	return maxPoolSize;
}

AActorPoolable *UCoinObjectPool::RequestPoolable()
{
	if (HasObjectAvailable(1))
	{
		AActorPoolable *object = availableObjects.Pop();
		object->SetIndex(usedObjects.Num());
		usedObjects.Push(object);
		object->OnActivate();
		object->SetActorTransform(GetOwner()->GetActorTransform());
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("Requested poolable."));

		return object;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No more available objects."));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("No more available objects."));

		return NULL;
	}
}

TArray<AActorPoolable *> UCoinObjectPool::RequestPoolableBatch(int size)
{
	TArray<AActorPoolable *> objects;
	for (size_t i = 0; i < size && availableObjects.Num() > 0; i++)
	{
		objects.Push(RequestPoolable());
	}

	return objects;
}

void UCoinObjectPool::ReleasePoolable(AActorPoolable *poolableObject)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("Releasing poolable."));

	poolableObject->OnRelease();
	usedObjects.Remove(poolableObject);
	availableObjects.Push(poolableObject);
}

void UCoinObjectPool::ReleasePoolableBatch(TArray<AActorPoolable *> objectList)
{
	for (auto obj : objectList)
	{
		ReleasePoolable(obj);
	}
}

void UCoinObjectPool::ReleasePoolableBatch(int count)
{
	for (size_t i = 0; i < count && usedObjects.Num() > 0; i++)
	{
		ReleasePoolable(usedObjects[i]);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolComponent.h"

// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ObjectPool = GetOwner()->FindComponentByClass<UCPP_ObjectPool>(); // Assuming object pool component is attached to the same owner
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	HandleInput();
}

void UObjectPoolComponent::SpawnObjects()
{
	if (ObjectPool)
	{
		ObjectPool->RequestPoolable();
	}
}

void UObjectPoolComponent::HandleInput()
{
	// Example: Trigger spawning when the 'Space' key is pressed
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Enter))
	{
		// Call spawning function
		SpawnObjects();
	}
}


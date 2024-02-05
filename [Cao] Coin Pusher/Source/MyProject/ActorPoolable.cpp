// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPoolable.h"

// Sets default values
AActorPoolable::AActorPoolable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorPoolable::BeginPlay()
{
	Super::BeginPlay();
	
	this->SetActorHiddenInGame(true);
	this->SetActorTickEnabled(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

// Called every frame
void AActorPoolable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorPoolable::OnInitialize()
{

}

void AActorPoolable::OnRelease()
{
	this->SetActorHiddenInGame(true);
	this->SetActorTickEnabled(false);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void AActorPoolable::OnActivate()
{
	this->SetActorHiddenInGame(false);
	this->SetActorTickEnabled(true);
	this->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
}

void AActorPoolable::SetIndex(int i)
{
	this->index = i;
}

int AActorPoolable::GetIndex() const
{
	return this->index;
}
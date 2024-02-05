// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPoolable.h"

void AActorPoolable::BeginPlay()
{
    Super::BeginPlay();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void AActorPoolable::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AActorPoolable::OnInitialize()
{
}

void AActorPoolable::OnRelease()
{
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
}

void AActorPoolable::OnActivate()
{
    SetActorHiddenInGame(false);
    SetActorTickEnabled(true);
    FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
}

void AActorPoolable::SetIndex(int i)
{
    index = i;
}

int AActorPoolable::GetIndex()
{
    return index;
}

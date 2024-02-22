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
	// UE_LOG(LogTemp, Display, TEXT("Initializing coin."));
	UMaterialInterface *mat = GetStaticMeshComponent()->GetMaterial(0);
	// UMaterialInstanceDynamic *dMat = CreateDynamicMaterialInstance(0, mat);
	UMaterialInstanceDynamic *dMat = UMaterialInstanceDynamic::Create(mat, NULL);

	// dMat->SetVectorParameterValue("Color", FLinearColor(FMath::RandRange(0, 255),
	// 													FMath::RandRange(0, 255),
	// 													FMath::RandRange(0, 255),
	// 													255));
	dMat->SetVectorParameterValue("Color", FLinearColor::MakeRandomColor());

	GetStaticMeshComponent()->SetMaterial(0, dMat);
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
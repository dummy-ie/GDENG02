// Fill out your copyright notice in the Description page of Project Settings.

#include "..\Game\RollaBallPlayer.h"
#include "..\Game\RollaBallGameModeBase.h"
#include "RollaBallItemBase.h"

// Sets default values
ARollaBallItemBase::ARollaBallItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallItemBase::OverlapBegin);
}

// Called when the game starts or when spawned
void ARollaBallItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ARollaBallItemBase::OverlapBegin(UPrimitiveComponent *OverlappedComponent,
									  AActor* OtherActor,
									  UPrimitiveComponent* OtherComp,
									  int32 OtherBodyIndex,
									  bool bFromSweep,
									  const FHitResult& SweepResult)
{
	if (Cast<ARollaBallPlayer>(OtherActor) != nullptr)
	{
		Collected();
		// OtherActor
	}
}

void ARollaBallItemBase::Collected_Implementation()
{
	ARollaBallGameModeBase* GameMode = Cast<ARollaBallGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}

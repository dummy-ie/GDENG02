// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolController.h"

// Sets default values for this component's properties
UPoolController::UPoolController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPoolController::BeginPlay()
{
	Super::BeginPlay();

	if (poolOwner)
	{
		pool = poolOwner->GetComponentByClass<UCoinObjectPool>();
		if (!ifPoolExists())
			return;
	}

	// find player controller
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// bind ENTER key to spawn a coin
		PlayerController->InputComponent->BindAction(SPAWN, IE_Pressed, this, &UPoolController::spawnCoin);
	}

	spawnInitialCoins();
}

// Called every frame
void UPoolController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// ticks += DeltaTime;

	// if (ticks > INTERVAL)
	// {
	// 	ticks = 0.0f;

	// 	if (!ifPoolExists())
	// 		return;

	// 	AActorPoolable *coin = pool->RequestPoolable();
	// 	if (!coin)
	// 	{
	// 		UE_LOG(LogTemp, Display, TEXT("coin is null!"));
	// 		if (GEngine)
	// 			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("coin is null!"));

	// 		return;
	// 	}

	// 	coin->SetActorLocation(FVector(0.0f, 0.0f, 100.0f));
	// }
}

void UPoolController::spawnCoin()
{
	if (!ifPoolExists())
		return;

	AActorPoolable *coin = pool->RequestPoolable();
	if (!coin)
	{
		UE_LOG(LogTemp, Display, TEXT("coin is null!"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("coin is null!"));

		return;
	}

	coin->SetActorLocation(FVector(FMath::RandRange(-170.0f, 170.0f), FMath::RandRange(-50.0f, 0.0f), FMath::RandRange(600.0f, 1000.0f)));
	coin->SetActorRotation(FRotator(FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f)));
}

void UPoolController::spawnInitialCoins()
{
	if (!ifPoolExists())
		return;

	TArray<AActorPoolable *> batch = pool->RequestPoolableBatch(500);
	for (auto &coin : batch)
	{
		coin->SetActorLocation(FVector(FMath::RandRange(-170.0f, 170.0f), FMath::RandRange(-60.0f, 120.0f), FMath::RandRange(100.0f, 600.0f)));
		coin->SetActorRotation(FRotator(FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f), FMath::RandRange(-180.0f, 180.0f)));
	}
}

bool UPoolController::ifPoolExists()
{
	if (!pool)
	{
		UE_LOG(LogTemp, Display, TEXT("Pool is null!"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Pool is null!"));

		return false;
	}

	return true;
}

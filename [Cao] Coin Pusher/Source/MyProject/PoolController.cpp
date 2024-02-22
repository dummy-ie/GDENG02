// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolController.h"

// Sets default values
APoolController::APoolController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APoolController::BeginPlay()
{
	Super::BeginPlay();
	ObjectPoolComponent = ObjectPool->FindComponentByClass<UCPP_ObjectPool>();

	if (!ObjectPoolComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Object Pool component not found in the scene"));
	}

	SetupPlayerInputComponent();

	if (Floor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Floor Found"));
		Floor->OnActorHit.AddDynamic(this, &APoolController::OnFloorHit);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Floor not Found"));
	}

	// Creates the UI widget and adds it to the viewport
	if (UIHUDClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIHUDClass is valid"));

		UIHUD = CreateWidget<UUIHUD>(GetWorld(), UIHUDClass);
		if (UIHUD)
		{
			UIHUD->AddToViewport();
			UIHUD->UpdateCoinCount(ReleasedCoinCount);
			UE_LOG(LogTemp, Warning, TEXT("UI widget added to viewport"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create UI widget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UIHUDClass is not assigned"));
	}
}

// Called every frame
void APoolController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APoolController::SetupPlayerInputComponent()
{
	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller not found!"));
		return;
	}

	InputComponent = PlayerController->InputComponent;
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not found on Player Controller!"));
		return;
	}

	InputComponent->BindAction("SpawnCoin", IE_Pressed, this, &APoolController::SpawnFromPool);
	InputComponent->BindAction("IncreaseCoins", IE_Pressed, this, &APoolController::IncreaseCoinSpawn);
	InputComponent->BindAction("DecreaseCoins", IE_Pressed, this, &APoolController::DecreaseCoinSpawn);
	UE_LOG(LogTemp, Warning, TEXT("Input binding successful."));
}

void APoolController::SpawnFromPool()
{
	for (size_t i = 0; i < coinsOnSpawn; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnFromPool called"));
		if (ObjectPoolComponent)
		{
			AActorPoolable *SpawnedActor = ObjectPoolComponent->RequestPoolable();

			if (SpawnedActor)
			{
				float RandomY = FMath::RandRange(-95.f, 95.f);

				SpawnedActor->SetActorLocationAndRotation(FVector(0.f, RandomY, 600.f),
														  FRotator(FMath::RandRange(-45.f, 45.f),
																   FMath::RandRange(-45.f, 45.f),
																   FMath::RandRange(-45.f, 45.f)));
			}
		}
	}
}

void APoolController::IncreaseCoinSpawn()
{
	if (coinsOnSpawn + 1 <= 20)
		coinsOnSpawn++;
}

void APoolController::DecreaseCoinSpawn()
{
	if (coinsOnSpawn - 1 >= 1)
		coinsOnSpawn--;
}

void APoolController::OnFloorHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Floor was hit"));

	// Checks if the collided actor is a poolable object
	AActorPoolable *PoolableActor = Cast<AActorPoolable>(OtherActor);
	if (PoolableActor)
	{
		// Calls ReleasePoolable to return the object to the pool
		if (ObjectPoolComponent)
		{
			ObjectPoolComponent->ReleasePoolable(PoolableActor);
			ReleasedCoinCount++;
			UIHUD->UpdateCoinCount(ReleasedCoinCount);
		}
	}
}
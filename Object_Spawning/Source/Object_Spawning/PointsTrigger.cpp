// Fill out your copyright notice in the Description page of Project Settings.

#include "PointsTrigger.h"

// Sets default values for this component's properties
UPointsTrigger::UPointsTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPointsTrigger::BeginPlay()
{
	Super::BeginPlay();

	// create widget and cast it to our UI
	if (gameWidgetClass)
	{
		gameWidget = Cast<UGameUI>(CreateWidget(GetWorld(), gameWidgetClass));

		if (gameWidget)
		{
			// now show the widget we created
			gameWidget->AddToViewport();
		}
	}

	// Bind the overlap event to the OnCollision function
	GetOwner()->GetComponentByClass<UStaticMeshComponent>()->OnComponentBeginOverlap.AddDynamic(this, &UPointsTrigger::OnCollision);
	
	// Initialize the object pool reference
	if (poolOwner)
	{
		pool = poolOwner->GetComponentByClass<UCoinObjectPool>();
		if (!pool)
		{
			UE_LOG(LogTemp, Display, TEXT("Pool is null!"));
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Pool is null!"));
		}
	}
}

// Called every frame
void UPointsTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPointsTrigger::OnCollision(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit)
{
	// cast the overlapped actor to the poolable coin
	AActorPoolable* coin = Cast<AActorPoolable>(OtherActor);

	if (coin)
	{
		if (!pool)
		{
			UE_LOG(LogTemp, Display, TEXT("Pool is null!"));
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Pool is null!"));

			return;
		}

		// increment score
		if (gameWidget)
			gameWidget->IncrementCoins();

		// release the overlapped coin
		pool->ReleasePoolable(coin);
	}
}
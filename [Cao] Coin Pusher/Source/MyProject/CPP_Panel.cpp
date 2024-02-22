// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Panel.h"

// Sets default values
ACPP_Panel::ACPP_Panel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PanelMesh"));
	RootComponent = PanelMesh;

	MovementSpeed = 75.0f;
	MaxDistance = 150.0f;
	InterpSpeed = MovementSpeed;

	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraintComponent"));
	PhysicsConstraintComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACPP_Panel::BeginPlay()
{
	Super::BeginPlay();

	// Gets the initial and target location upon starting.
	InitialLocation = GetActorLocation();
	TargetLocation = InitialLocation + FVector(MaxDistance, 0.0f, 0.0f);

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

	InputComponent->BindAction("IncreasePusherSpeed", IE_Pressed, this, &ACPP_Panel::IncreaseSpeed);
	InputComponent->BindAction("DecreasePusherSpeed", IE_Pressed, this, &ACPP_Panel::DecreaseSpeed);
	UE_LOG(LogTemp, Warning, TEXT("Input binding CPP Panel successful."));
}

// void ACPP_Panel::SetupPlayerInputComponent()
// {
// 	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
// 	if (!PlayerController)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Player Controller not found!"));
// 		return;
// 	}

// 	InputComponent = PlayerController->InputComponent;
// 	if (!InputComponent)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Input Component not found on Player Controller!"));
// 		return;
// 	}

// 	InputComponent->BindAction("IncreasePusherSpeed", IE_Pressed, this, &ACPP_Panel::IncreaseSpeed);
// 	InputComponent->BindAction("DecreasePusherSpeed", IE_Pressed, this, &ACPP_Panel::DecreaseSpeed);
// 	UE_LOG(LogTemp, Warning, TEXT("Input binding CPP Panel successful."));
// }

// Called every frame
void ACPP_Panel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	// Interpolates to the target location from wherever the actor is.
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MovementSpeed * speedMultiplier);
	SetActorLocation(NewLocation);

	// Swaps initial and target locations so that it loops.
	if (GetActorLocation() == TargetLocation)
	{
		FVector temp = InitialLocation;
		InitialLocation = TargetLocation;
		TargetLocation = temp;
	}
}

void ACPP_Panel::IncreaseSpeed()
{
	UE_LOG(LogTemp, Display, TEXT("Increasing pusher speed to %d."), speedMultiplier);

	if (speedMultiplier + 1 <= 10)
		speedMultiplier++;
}

void ACPP_Panel::DecreaseSpeed()
{
	if (speedMultiplier - 1 >= 1)
		speedMultiplier--;
}

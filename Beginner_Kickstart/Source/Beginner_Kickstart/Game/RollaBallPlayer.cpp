// Fill out your copyright notice in the Description page of Project Settings.

#include "RollaBallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollaBallPlayer::Jump);
}

void ARollaBallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollaBallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollaBallPlayer::Jump()
{
	if (JumpCount >= MaxJumpCount)
		return;

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));

	JumpCount++;
}

void ARollaBallPlayer::OnHit(UPrimitiveComponent *HitComponent,
							 AActor *OtherActor,
							 UPrimitiveComponent *OtherComp,
							 FVector NormalImpulse,
							 const FHitResult &Hit)
{
	const float HitDirection = Hit.Normal.Z;
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, FString::Printf(TEXT("Z Normal: %f"), HitDirection));

	if (HitDirection > 0)
	{
		JumpCount = 0;
	}
}

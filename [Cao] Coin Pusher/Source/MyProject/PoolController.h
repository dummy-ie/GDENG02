// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h" // For UserWidget base class
#include "Components/TextBlock.h" // For displaying text in the UI
#include "Components/InputComponent.h"	
#include "CPP_ObjectPool.h"
#include "UIHUD.h"
#include "Kismet/GameplayStatics.h"
#include "PoolController.generated.h"


UCLASS()
class MYPROJECT_API APoolController : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent();

	UFUNCTION()
	void OnFloorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void SpawnFromPool();

	void IncreaseCoinSpawn();

	void DecreaseCoinSpawn();

	UPROPERTY(EditAnywhere)
	AActor* ObjectPool;			// The actor handling all poolable objects.

	UPROPERTY(EditAnywhere)
	AStaticMeshActor* Floor;	// Can be any actor that can call ReleasePoolable once the coin collides with it.

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUIHUD> UIHUDClass;
	UUIHUD* UIHUD;

private:
	UCPP_ObjectPool* ObjectPoolComponent;
	// Variable to store the number of released coins
	int32 ReleasedCoinCount = 0;
	int coinsOnSpawn = 1;
};

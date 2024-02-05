// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectSpawner.generated.h"

UCLASS()
class MYPROJECT_API AObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere) AActor* actorCopy = NULL;
	UPROPERTY(EditAnywhere) int spawnLimit = 10;
	float ticks = 0.0f;
	float destroyTicks = 0.0f;
	float INTERVAL = 1.0f;
	float DELETE_INTERVAL = 10.0f;

	TArray<AActor*> spawnedObjects;

	void DeleteAll();
};

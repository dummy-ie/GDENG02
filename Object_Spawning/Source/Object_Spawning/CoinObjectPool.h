// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPoolable.h"
#include "CoinObjectPool.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OBJECT_SPAWNING_API UCoinObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCoinObjectPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void Initialize();
	bool HasObjectAvailable(int requestSize);
	int GetMaxPoolSize();
	AActorPoolable *RequestPoolable();
	TArray<AActorPoolable *> RequestPoolableBatch(int size);

	void ReleasePoolable(AActorPoolable *poolableObject);
	void ReleasePoolableBatch(TArray<AActorPoolable *> objectList);
	void ReleasePoolableBatch(int count);

private:
	UPROPERTY(EditAnywhere)
	int maxPoolSize = 20;
	
	UPROPERTY(EditAnywhere)
	AActorPoolable *actorCopy = NULL;
	
	UPROPERTY(EditAnywhere)
	AActor *parent = NULL;
	

	TArray<AActorPoolable *> availableObjects;
	TArray<AActorPoolable *> usedObjects;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ActorPoolable.generated.h"

/**
 *
 */
UCLASS()
class OBJECT_SPAWNING_API AActorPoolable : public AStaticMeshActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void OnInitialize();
	virtual void OnRelease();
	virtual void OnActivate();

	void SetIndex(int i);
	int GetIndex();

private:
	int index = -1;
};

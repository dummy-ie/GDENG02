// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinObjectPool.h"
#include "GameUI.h"
#include "Blueprint/UserWidget.h"
#include "PointsTrigger.generated.h"

class UGameUI;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OBJECT_SPAWNING_API UPointsTrigger : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPointsTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit);
	// void OnOverlap(class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> gameWidgetClass;

	UPROPERTY()
	UGameUI *gameWidget;

	UPROPERTY(EditAnywhere)
	AActor *poolOwner = NULL;

	UCoinObjectPool *pool = NULL;
};

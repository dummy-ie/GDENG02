// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUI.generated.h"

/**
 * 
 */
UCLASS()
class OBJECT_SPAWNING_API UGameUI : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		// SetCoinText(int coins);
		UFUNCTION(BlueprintImplementableEvent)
		void IncrementCoins();
};

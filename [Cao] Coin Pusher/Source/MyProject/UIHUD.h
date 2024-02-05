// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UIHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UUIHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    // Function to update the displayed coin count
    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateCoinCount(int32 NewCoinCount);

private:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* CoinCountText;
	
};

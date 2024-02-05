// Fill out your copyright notice in the Description page of Project Settings.


#include "UIHUD.h"

void UUIHUD::UpdateCoinCount(int32 NewCoinCount)
{
    if (CoinCountText)
    {
        CoinCountText->SetText(FText::FromString(FString::Printf
                    (TEXT("Coins Released: %d"), NewCoinCount)));
    }
}
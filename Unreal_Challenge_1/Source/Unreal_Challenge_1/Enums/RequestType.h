// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM(BlueprintType)
enum class RequestType : uint8
	{
		NONE UMETA(DisplayName = "None"),
		DELIVER_INPUT UMETA(DisplayName = "Deliver Input"),
		TAKE_OUTPUT UMETA(DisplayName = "Take Output")
	};

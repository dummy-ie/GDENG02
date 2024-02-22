// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM(BlueprintType)
enum class ResourceType : uint8
{
	NONE,
	IRON UMETA(DisplayName = "Iron"),
	COAL UMETA(DisplayName = "Coal"),
	STEEL_BEAM UMETA(DisplayName = "Steel Beam"),
	LUMBER UMETA(DisplayName = "Lumber"),
	SEWING_MACHINE UMETA(DisplayName = "Sewing Machine")
};

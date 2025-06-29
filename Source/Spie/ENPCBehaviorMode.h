// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ENPCBehaviorMode.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBehaviorMode :uint8
{
	Patrol UMETA(DisplayName = "Patrol"),
	Search UMETA(DisplayName = "Search"),
	Combat UMETA(DisplayName = "Combat")
};

UCLASS()
class SPIE_API UENPCBehaviorMode : public UObject
{
	GENERATED_BODY()

};

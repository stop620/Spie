// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NPCBase.h"
#include "BaseQuest.generated.h"

UENUM(BlueprintType)
enum class EQuestReward : uint8
{
	E_Pay	UMETA(DisplayName = "Pay")
};

UENUM(BlueprintType)
enum class EClearCondition : uint8
{
	E_Default	UMETA(DisplayName = "Default"),
	E_Collect	UMETA(DisplayName = "Collect"),
	E_Kill		UMETA(DisplayName = "Kill"),
	E_Delivery	UMETA(DisplayName = "Delivery"),
	E_Interact	UMETA(DisplayName = "Interact")
};

USTRUCT(BlueprintType)
struct FReward
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestReward RewardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Pay;
};

USTRUCT(BlueprintType)
struct FObjective : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Client;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EClearCondition ClearType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemToCollect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ANPCBase> TargetEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RequireCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSuccess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FReward Rewards;
};
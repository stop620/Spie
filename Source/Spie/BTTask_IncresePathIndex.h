// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncresePathIndex.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API UBTTask_IncresePathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public: 
	UBTTask_IncresePathIndex();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	enum class EDirectionType { Forward, Reverse };

	EDirectionType Direction = EDirectionType::Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	bool bBiDirectinal = false;
	
};

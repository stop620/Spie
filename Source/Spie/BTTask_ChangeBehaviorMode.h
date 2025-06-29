// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ENPCBehaviorMode.h"
#include "BTTask_ChangeBehaviorMode.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API UBTTask_ChangeBehaviorMode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChangeBehaviorMode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category=Blackboard, meta=(AllowPrivateAccess=true))
	EBehaviorMode Mode;
};

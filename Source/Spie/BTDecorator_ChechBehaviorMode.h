// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "ENPCBehaviorMode.h"

#include "BTDecorator_ChechBehaviorMode.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API UBTDecorator_ChechBehaviorMode : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_ChechBehaviorMode();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	UPROPERTY(EditAnywhere, Category=Blackboard)
	EBehaviorMode Mode = EBehaviorMode::Patrol;
private:


};

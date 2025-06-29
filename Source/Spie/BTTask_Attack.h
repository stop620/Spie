// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Attack.generated.h"

class ANPCBase;

UCLASS()
class SPIE_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	float RandomRadius = 50.f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetRandomShootTime.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API UBTService_SetRandomShootTime : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_SetRandomShootTime();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

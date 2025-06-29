// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetRandomShootTime.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetRandomShootTime::UBTService_SetRandomShootTime()
{
    NodeName = TEXT("Set Random Int");
}

void UBTService_SetRandomShootTime::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    int Count = FMath::RandRange(1, 3);
    OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), Count);
}

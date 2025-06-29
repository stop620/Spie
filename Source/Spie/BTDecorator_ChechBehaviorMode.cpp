// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_ChechBehaviorMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NPCBase.h"

UBTDecorator_ChechBehaviorMode::UBTDecorator_ChechBehaviorMode()
{
    NodeName = TEXT("Check Behavior Mode");

    INIT_DECORATOR_NODE_NOTIFY_FLAGS();
}

bool UBTDecorator_ChechBehaviorMode::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    ANPCBase* NPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());

    if (NPC)
    {
        uint8 Key =OwnerComp.GetBlackboardComponent()->GetValueAsEnum(GetSelectedBlackboardKey());
        bool bResult = (Key == uint8(Mode));
        return bResult;
    }
    return false;
}
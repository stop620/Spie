// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookAround.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NPCBase.h"
#include "AIController.h"

UBTTask_LookAround::UBTTask_LookAround()
{
    NodeName = TEXT("Look Around");
}

EBTNodeResult::Type UBTTask_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ANPCBase* NPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
    if (NPC)
    {
        NPC->bShouldLookAround = true;

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

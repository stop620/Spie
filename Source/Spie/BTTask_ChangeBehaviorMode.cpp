// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChangeBehaviorMode.h"
#include "AIController.h"
#include "NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ChangeBehaviorMode::UBTTask_ChangeBehaviorMode()
{
    NodeName = TEXT("Change Mode");
}

EBTNodeResult::Type UBTTask_ChangeBehaviorMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ANPCBase* NPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
    if (NPC)
    {
        NPC->SetBehaviorMode(Mode);

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

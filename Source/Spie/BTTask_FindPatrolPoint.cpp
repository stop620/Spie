// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPoint.h"
#include "AIController.h"
#include "NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_PatrolPath.h"

UBTTask_FindPatrolPoint::UBTTask_FindPatrolPoint()
{
    NodeName = TEXT("Find Patrol Point");
}

EBTNodeResult::Type UBTTask_FindPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    ANPCBase* NPC = Cast<ANPCBase>(AIController->GetPawn());
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (AIController != nullptr && NPC->GetPatrolPath() != nullptr)
    {
        if (BlackboardComp)
        {
            int Index = BlackboardComp->GetValueAsInt(GetSelectedBlackboardKey());
            
            FVector Point = NPC->GetPatrolPath()->GetPatrolPoint(Index);

            FVector GlobalPoint = NPC->GetPatrolPath()->GetActorTransform().TransformPosition(Point);

            BlackboardComp->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}

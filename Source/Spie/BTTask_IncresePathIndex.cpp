// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncresePathIndex.h"
#include "AIController.h"
#include "NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncresePathIndex::UBTTask_IncresePathIndex()
{
    NodeName = TEXT("Increase Path Index");
}

EBTNodeResult::Type UBTTask_IncresePathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    if (AIController)
    {
        ANPCBase* NPC = Cast<ANPCBase>(AIController->GetPawn());
        if (NPC)
        {
            UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

            int PointsCount = NPC->GetPatrolPath()->Num();
            int MinIndex = 0;
            int MaxIndex = PointsCount - 1;
            int Index = BlackboardComp->GetValueAsInt(GetSelectedBlackboardKey());

            if (bBiDirectinal)
            {
                if (Index >= MaxIndex && Direction == EDirectionType::Forward)
                {
                    Direction = EDirectionType::Reverse;
                }
                else if (Index == MinIndex && Direction == EDirectionType::Reverse)
                {
                    Direction = EDirectionType::Forward;
                }
            }

            BlackboardComp->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirectionType::Forward ? ++Index : --Index) % PointsCount);

            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}

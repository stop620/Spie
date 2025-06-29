// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
    NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (OwnerComp.GetAIOwner() != nullptr)
    {
        FVector Target = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
        FNavLocation NewLocation;
        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

        if (NavSystem)
        {
            NavSystem->GetRandomPointInNavigableRadius(Target, SearchRadius, NewLocation);
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NewLocation.Location);

            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}

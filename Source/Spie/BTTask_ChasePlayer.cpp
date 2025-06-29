// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    bool CanSee = OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanSeePlayer");
    bool InRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool("InRange");
    if (AIController)
    {
       
        FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

        AIController->MoveToLocation(PlayerLocation, Radius);
        if (InRange && CanSee)
        {
            AIController->StopMovement();

        }
        
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

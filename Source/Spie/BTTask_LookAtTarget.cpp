// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookAtTarget.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_LookAtTarget::UBTTask_LookAtTarget(const FObjectInitializer& ObjectInitializer)
{
    NodeName = TEXT("Look At Target");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    
    return EBTNodeResult::InProgress;

}

void UBTTask_LookAtTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
    if (!OwnerComp.GetAIOwner())
    {
        return;
    }
    RotateToTarget(OwnerComp, DeltaTime);
}

void UBTTask_LookAtTarget::RotateToTarget(UBehaviorTreeComponent& OwnerComp, float DeltaTime)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        APawn* NPC = AIController->GetPawn();
        if (NPC)
        {
            FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
            FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(NPC->GetActorLocation(), TargetLocation);
            NPC->SetActorRotation(FMath::RInterpTo(NPC->GetActorRotation(), TargetRotation, DeltaTime, 3.f));

            if (TargetRotation.Equals(NPC->GetActorRotation(), 5.0f) == true)
            {
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

                
            }
        }
    }
}

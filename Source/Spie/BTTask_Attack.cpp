// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "NPCBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"


UBTTask_Attack::UBTTask_Attack()
{
    NodeName = TEXT("Shoot Player");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ANPCBase* NPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
    AAIController* const AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    if (AIController)
    {
        ACharacterBase* Player = Cast<ACharacterBase>(AIController->GetBlackboardComponent()->GetValueAsObject("Player"));
        if (Player->IsDead() == false)
        {
            FVector Target = OwnerComp.GetBlackboardComponent()->GetValueAsVector("TargetLocation");

            FVector RandomVector;
            RandomVector.X = FMath::RandRange(-RandomRadius, RandomRadius);
            RandomVector.Y = FMath::RandRange(-RandomRadius, RandomRadius);
            RandomVector.Z = FMath::RandRange(-RandomRadius, RandomRadius);
            if (NPC->CurrentAmmo == 0)
            {
                NPC->ReloadWeapon();
            }
            else
            {
                NPC->CurrentWeapon->ActivateWeapon(Target - RandomVector);
            }
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}

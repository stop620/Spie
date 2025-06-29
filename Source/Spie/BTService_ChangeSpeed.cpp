// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"
#include "AIController.h"
#include "NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
    bNotifyBecomeRelevant = true;
    NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    ANPCBase* NPC = Cast<ANPCBase>(AIController->GetPawn());
    if (AIController)
    {
        if (NPC)
        {
            Cast<UCharacterMovementComponent>(NPC->GetMovementComponent())->MaxWalkSpeed = Speed;
            
        }
    }
}

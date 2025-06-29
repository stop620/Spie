// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SpyCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* AIPawn = AIController->GetPawn();
    ASpyCharacter* PlayerPawn = Cast<ASpyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));

    if (AIController->LineOfSightTo(PlayerPawn))
    {
        FVector PlayerLocation = PlayerPawn->GetActorLocation();
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
        FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
        FRotator TargetRotation = UKismetMathLibrary::RInterpTo(AIPawn->GetActorRotation(), LookRotation, DeltaSeconds, RotateSpeed);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject("Player", PlayerPawn);

        if (AIPawn->GetActorRotation().Equals(TargetRotation, 1e-3f) == false)
        {
            AIPawn->SetActorRotation(TargetRotation);
        }
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);

    }
    
}

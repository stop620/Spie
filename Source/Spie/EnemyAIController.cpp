// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "NPCBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyAIController::AEnemyAIController()
{
    SetupPerceptionSystem();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    NPC = Cast<ANPCBase>(InPawn);
    if (NPC)
    {
        SetControlRotation(InPawn->GetActorRotation());
        if (UBehaviorTree* Behavior = NPC->GetBehaviorTree())
        {
            UBlackboardComponent* BlackBoard;
            UseBlackboard(Behavior->BlackboardAsset, BlackBoard);
            RunBehaviorTree(Behavior);
        }
        TeamId = FGenericTeamId(NPC->ID);
    }
    
}

void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    bool CanSee = GetBlackboardComponent()->GetValueAsBool("CanSeePlayer");
    bool bOnSight = GetBlackboardComponent()->GetValueAsBool("DetectedBySight");

    if (CanSee || bOnSight)
    {
        APawn* Player = Cast<APawn>(GetBlackboardComponent()->GetValueAsObject("Player"));
        float Distance = FVector::Dist(NPC->GetActorLocation(), Player->GetActorLocation());

        if (Distance < NPC->Range)
        {
            NPC->SetBehaviorMode(EBehaviorMode::Combat);
            GetBlackboardComponent()->SetValueAsBool("InRange", true);
        }
        else
        {
            GetBlackboardComponent()->SetValueAsBool("InRange", false);
        }
    }
    
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& other) const
{
    const ACharacterBase* OtherCharacter = Cast<ACharacterBase>(&other);
    FGenericTeamId OtherActorTeamId = OtherCharacter->GetGenericTeamId();
    FGenericTeamId ControlledTeamId = GetGenericTeamId();
    UE_LOG(LogTemp, Warning, TEXT("CheckTeam"));
    if (OtherActorTeamId == 0)
    {
        return ETeamAttitude::Neutral;
    }
    else if (OtherActorTeamId == TeamId)
    {
        return ETeamAttitude::Friendly;
    }
    else
    {
        return ETeamAttitude::Hostile;
    }
}

void AEnemyAIController::SetBlackboardTargetLocation(FVector Location)
{
    GetBlackboardComponent()->SetValueAsVector("TargetLocation", Location);

}

FGenericTeamId AEnemyAIController::GetGenericTeamId() const
{
    return TeamId;
}

void AEnemyAIController::SetupPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

    if (SightConfig != nullptr || HearingConfig != nullptr) 
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component"));
    }
    if (SightConfig)
    {
        SightConfig->SightRadius = 900.f;
        SightConfig->LoseSightRadius = 920.f;
        SightConfig->PeripheralVisionAngleDegrees = 40.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->ConfigureSense(*SightConfig);
    }
    if (HearingConfig)
    {
        HearingConfig->HearingRange = 700.f;
        HearingConfig->SetMaxAge(5.f);
        HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
        HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
        HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;

        GetPerceptionComponent()->ConfigureSense(*HearingConfig);
    }

    if (SightConfig != nullptr || HearingConfig != nullptr)
    {
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
    }
}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
    FAISenseID SightID = UAISense::GetSenseID<UAISense_Sight>();
    FAISenseID HearingID = UAISense::GetSenseID<UAISense_Hearing>();
    GetBlackboardComponent()->SetValueAsObject("Player", Actor);

    if (NPC->GetBehaviorMode() != EBehaviorMode::Combat)
    {
        SetBlackboardTargetLocation(Actor->GetActorLocation());
        if (Stimulus.Type == SightID)
        {
            GetBlackboardComponent()->SetValueAsBool("DetectedBySight", Stimulus.WasSuccessfullySensed());
            NPC->SetBehaviorMode(EBehaviorMode::Search);
        }
        else if (Stimulus.Type == HearingID)
        {
            NPC->SetBehaviorMode(EBehaviorMode::Search);

        }
    }
}

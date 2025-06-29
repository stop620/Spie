// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class ANPCBase;

UCLASS()
class SPIE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();
	void SetBlackboardTargetLocation(FVector Location);

	virtual FGenericTeamId GetGenericTeamId() const override;
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	FGenericTeamId TeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& other) const override;

private:
	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	ANPCBase* NPC;

	UPROPERTY(EditAnywhere, Category = "Perception")
	UAIPerceptionComponent* PerceptionComp;
	UPROPERTY(EditAnywhere, Category = "Perception")
	UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere, Category = "Perception")
	UAISenseConfig_Hearing* HearingConfig;
};

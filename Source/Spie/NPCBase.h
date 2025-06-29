// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "AI_PatrolPath.h"
#include "ENPCBehaviorMode.h"

#include "NPCBase.generated.h"

class UHealthComponent;
class UBehaviorTree;

UCLASS()
class SPIE_API ANPCBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBase();

	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const;

	AAI_PatrolPath* GetPatrolPath() const;

	void SetBehaviorMode(EBehaviorMode State);
	EBehaviorMode GetBehaviorMode();

	void Die();

	UFUNCTION(BlueprintCallable)
	bool IsDead();

	UPROPERTY(EditAnywhere, Category=AI)
	float Range = 550.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Anim)
	bool bShouldLookAround = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess="true"))
	UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	AAI_PatrolPath* PatrolPath;

private:
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = state, meta=(AllowPrivateAccess=true))
	EBehaviorMode BehaviorMode;
};

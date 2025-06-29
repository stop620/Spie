// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"
#include "HealthComponent.h"
#include "AI_PatrolPath.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ENPCBehaviorMode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->ComponentTags.Add("Enemy Body");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");


}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetBehaviorMode(EBehaviorMode::Patrol);

}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBehaviorTree* ANPCBase::GetBehaviorTree() const
{
	return AIBehavior;
}

AAI_PatrolPath* ANPCBase::GetPatrolPath() const
{
	return PatrolPath;
}

void ANPCBase::SetBehaviorMode(EBehaviorMode State)
{
	BehaviorMode = State;
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		if (State == EBehaviorMode::Combat)
		{

		}
		AIController->GetBlackboardComponent()->SetValueAsEnum("Mode", uint8(BehaviorMode));
	}
}


EBehaviorMode ANPCBase::GetBehaviorMode()
{
	return BehaviorMode;
}

void ANPCBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Dead."), *GetName());
	if(!bIsDead)
	{
		if (CurrentWeapon != nullptr)
		{
			CurrentWeapon->Destroy();
		}
		PrimaryActorTick.bCanEverTick = false;
		DetachFromControllerPendingDestroy();
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetMesh()->SetCollisionProfileName(TEXT("GrabbableRagdoll"));
		GetMesh()->SetGenerateOverlapEvents(true);
		SetActorEnableCollision(true);

		//RagDoll
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;

		UCharacterMovementComponent* MovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (MovementComp)
		{
			MovementComp->StopMovementImmediately();
			MovementComp->DisableMovement();
			MovementComp->SetComponentTickEnabled(false);
		}

		bIsDead = true;
	}
	
}

bool ANPCBase::IsDead()
{
	return bIsDead;
}


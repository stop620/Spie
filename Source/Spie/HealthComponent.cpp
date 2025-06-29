// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFrameWork/Character.h"
#include "Components/CapsuleComponent.h"
#include "SpyCharacter.h"
#include "NPCBase.h"
#include "math.h"
#include "SpyPlayerController.h"
#include "EnemyAIController.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCausor)
{

	if (DamagedActor == DamageCausor && Damage == 0.f)
	{
		return;
	}
	//if DamageCausor is Player
	if (ASpyCharacter* Player = Cast<ASpyCharacter>(DamageCausor))
	{
		if (Player == Cast<ASpyCharacter>(DamagedActor))
		{
			return;
		}
		if (CurrentHealth == DefaultHealth)
		{
			if (ASpyPlayerController* Controller = Cast<ASpyPlayerController>(Instigator))
			{
				ANPCBase* NPC = Cast<ANPCBase>(DamagedActor);
				NPC->SetBehaviorMode(EBehaviorMode::Combat);
				AEnemyAIController* AIController = Cast<AEnemyAIController>(NPC->GetController());
				AIController->SetBlackboardTargetLocation(DamageCausor->GetActorLocation());
			}
		}
		float DamageApplied = FMath::Min(Damage, CurrentHealth);
		CurrentHealth = CurrentHealth - DamageApplied;

		if (CurrentHealth == 0.f)
		{
			Cast<ANPCBase>(DamagedActor)->Die();
		}
	}
	//if DamageCausor is NPC
	else if (ANPCBase* NPC = Cast<ANPCBase>(DamageCausor))
	{
		float DamageApplied = FMath::Min(Damage, CurrentHealth);
		CurrentHealth = CurrentHealth - DamageApplied;

		if (CurrentHealth == 0.f)
		{
			Cast<ASpyCharacter>(DamagedActor)->Die();

			
		}
	}
}


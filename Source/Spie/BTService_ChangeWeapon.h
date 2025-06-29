// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "WeaponType.h"

#include "BTService_ChangeWeapon.generated.h"


UCLASS()
class SPIE_API UBTService_ChangeWeapon : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_ChangeWeapon();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category=Blackboard)
	EWeaponType SelectedWeapon = EWeaponType::Unarmed;

	float data = 1.0f;
};

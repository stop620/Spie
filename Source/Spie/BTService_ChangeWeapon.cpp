// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeWeapon.h"
#include "NPCBase.h"
#include "AIController.h"
#include "WeaponType.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_ChangeWeapon::UBTService_ChangeWeapon()
{
    bNotifyBecomeRelevant = true;
    NodeName = "Change Weapon to Selected Value";
    bTickIntervals = false;
}

void UBTService_ChangeWeapon::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ANPCBase* NPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
    
    if (NPC)
    {
        switch (SelectedWeapon)
        {
        case EWeaponType::Unarmed :
            NPC->ChangeToUnarmed();
            break;

        case EWeaponType::Pistol :
            NPC->ChangeToPistol();
            if (NPC->bShouldLookAround == true)
            {
                NPC->bShouldLookAround = false;
            }
            
            break;

        default:
            break;
        }
    }
}

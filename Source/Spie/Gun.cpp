// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBase.h"
#include "Bullet.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AGun::AGun()
{
}

void AGun::BeginPlay()
{
    Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

void AGun::ActivateWeapon(FVector TargetLocation)
{

    if(bIsEquiped)
    {
        ACharacterBase* OwnerCharacter = Cast<ACharacterBase>(GetOwner());
        if (OwnerCharacter != nullptr)
        {
            if (OwnerCharacter->CurrentAmmo != 0 && OwnerCharacter->IsReloading != true)
            {
                Mesh->PlayAnimation(FireAnim, false);
                FHitResult Hit;
                FVector ShootDirection;
                bool bHit = GunTrace(Hit, ShootDirection, TargetLocation);
                AActor* HitActor = Hit.GetActor();
                
                if (bHit)
                {
                    FRotator BulletRotation = ShootDirection.Rotation();
                    float Distance = FVector::Dist(Mesh->GetSocketLocation(FName("MuzzleFlash")), Hit.Location);
                    ABullet* FiredBullet = GetWorld()->SpawnActor<ABullet>(Bullet, Hit.Location, BulletRotation);
                    FiredBullet->BulletTrail->SetNiagaraVariableVec3(FString("BeamEnd"), FVector(Distance, 0.f, 0.f));


                    //DrawDebugSphere(GetWorld(), Hit.Location, 2.f, 12, FColor::Red, true);
                    if (Hit.BoneName == "Head") // HeadShot
                    {
                        UGameplayStatics::ApplyDamage(HitActor, Damage * 3.0f, GetOwnerController(), GetOwner(), UDamageType::StaticClass());
                    }
                    else // Body
                    {
                        UGameplayStatics::ApplyDamage(HitActor, Damage, GetOwnerController(), GetOwner(), UDamageType::StaticClass());
                    }
                }
                else
                {
                    FVector Start = Mesh->GetSocketLocation(TEXT("MuzzleFlash"));
                    FVector MaxLocation = Start + (TargetLocation - Start).Rotation().Vector() * Range;
                    float Distance = FVector::Dist(TargetLocation, Start);
                    ABullet* FiredBullet = GetWorld()->SpawnActor<ABullet>(Bullet, MaxLocation, (TargetLocation - Start).Rotation());
                    FiredBullet->BulletTrail->SetNiagaraVariableVec3(FString("BeamEnd"), FVector(Distance, 0.f, 0.f));
                }
                OwnerCharacter->CurrentAmmo -= 1;
            }
        }
        
    }
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShootDirection, FVector TargetLocation)
{
    FCollisionShape BulletSphere = FCollisionShape::MakeSphere(BulletSize);
    //FHitResult MouseHit;
    //Cast<APlayerController>(GetOwnerController())->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, MouseHit);
    
    FVector Start = Mesh->GetSocketLocation(TEXT("MuzzleFlash"));
    FVector End = Start + (TargetLocation - Start).Rotation().Vector() * Range;
    ShootDirection = End - Start;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());
    //DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3.f);

    return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, BulletSphere, Params);
}

AController* AGun::GetOwnerController()
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr)
    {
        return nullptr;
    }
    AController* OwnerController = OwnerPawn->GetController();

    return OwnerController;
}

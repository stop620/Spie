// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

class UNiagaraComponent;

class ABullet;

UCLASS()
class SPIE_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:
	AGun();

	virtual void ActivateWeapon(FVector TargetLocation) override;
	bool GunTrace(FHitResult& HitResult, FVector& ShootDirection, FVector TargetLocation);
	AController* GetOwnerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage = 0.f;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Range = 0.f;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BulletSize = 0.f;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	UAnimSequence* FireAnim;
	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<ABullet> Bullet;
	UPROPERTY(EditAnywhere, Category=Weapon)
	UNiagaraComponent* BulletTrail;
	
};

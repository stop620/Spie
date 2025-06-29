// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "WeaponType.h"
#include "GenericTeamAgentInterface.h"
#include "CharacterBase.generated.h"

class AGun;

UCLASS()
class SPIE_API ACharacterBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UFUNCTION(BlueprintCallable)
	virtual void Die();

	UFUNCTION(BlueprintCallable)
	void ReloadEnd();

	virtual bool IsDead();

	void ChangeToUnarmed();
	void ChangeToPistol();
	void ReloadWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	int32 ID = 0;

	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	FGenericTeamId TeamId;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	

	AWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	EWeaponType CurrentWeaponType;

	UPROPERTY(EditAnywhere, Category = Items)
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items)
	bool bIsEquippedWeapon = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	int CurrentAmmo = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	int MaxAmmo = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	int RemainAmmo = 24;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsReloading = false;

	bool bIsDead = false;
private:
	
	
};

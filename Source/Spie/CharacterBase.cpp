// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Pistol.h"
#include "Gun.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentWeaponType = EWeaponType::Unarmed;

}

void ACharacterBase::Die()
{
}

void ACharacterBase::ReloadEnd()
{
	if (RemainAmmo < (MaxAmmo - CurrentAmmo))
	{
		CurrentAmmo = (RemainAmmo + CurrentAmmo);
		RemainAmmo = 0;
	}
	else
	{
		RemainAmmo = RemainAmmo - (MaxAmmo - CurrentAmmo);
		CurrentAmmo = MaxAmmo;
	}
}

bool ACharacterBase::IsDead()
{
	return false;
}

void ACharacterBase::ChangeToUnarmed()
{

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	CurrentWeaponType = EWeaponType::Unarmed;
}

void ACharacterBase::ChangeToPistol()
{
	if (!CurrentWeapon)
	{
		if (WeaponClass != nullptr)
		{
			CurrentWeapon = GetWorld()->SpawnActor<APistol>(WeaponClass, GetActorLocation(), GetActorRotation());
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon");
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->bIsEquiped = true;
		}
		
	}

	CurrentWeaponType = EWeaponType::Pistol;
}

void ACharacterBase::ReloadWeapon()
{
	if (bIsDead == false && CurrentWeapon != nullptr && RemainAmmo != 0 && IsReloading != true && CurrentAmmo != MaxAmmo)
	{
		IsReloading = true;
		UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
	}
}

FGenericTeamId ACharacterBase::GetGenericTeamId() const
{
	return TeamId;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	TeamId = ID;
}



// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


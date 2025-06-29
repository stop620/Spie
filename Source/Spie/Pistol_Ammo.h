// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Components/BoxComponent.h"
#include "CharacterBase.h"
#include "Pistol_Ammo.generated.h"

UCLASS()
class SPIE_API APistol_Ammo : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APistol_Ammo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetItem(ACharacterBase* Character) override;

private:
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* AmmoBoxMesh;
	UPROPERTY(EditAnywhere, Category = Bullet)
	int BulletNum = 0;
	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	USoundBase* PickupSound;
};

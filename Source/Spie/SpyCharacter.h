// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterBasePawn.h"
#include "InputActionValue.h"
#include "SpyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UHealthComponent;
class AWeapon;
class UAIPerceptionStimuliSourceComponent;
class ASpyPlayerController;
class UPhysicsHandleComponent;
class UGrabber;

UCLASS()
class SPIE_API ASpyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	ASpyCharacter();

	void ZoomOut(float Value);

	void Equip(AWeapon* Weapon);
	void GrabEnemyBody(UPrimitiveComponent* EnemyMesh);
	void ReleaseEnemyBody();
	void ThrowGrenade();

	virtual void Die() override;

	virtual bool IsDead() override;
	bool bBodyGrab = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = weapon)
	int GrenadeCount = 2;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Components", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGrabber* GrabComp;

	UPROPERTY(EditAnywhere, Category=weapon)
	TSubclassOf<AActor> Grenade;

	UCharacterMovementComponent* MoveComp;

	UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();
	void RemoveStumulusSource();

	FRotator CameraAngle = { -60.f, 0.f, 0.f };
	float MaxCameraDistance = 1100.f;
	float MinCameraDistance = 200.f;

	ASpyPlayerController* Controller;
};

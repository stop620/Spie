// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "HealthComponent.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "perception/AISense_Hearing.h"
#include "Components/CapsuleComponent.h"
#include "SpyPlayerController.h"
#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
ASpyCharacter::ASpyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	MoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	MoveComp->bOrientRotationToMovement = false;
	MoveComp->NavAgentProps.bCanCrouch = true;
	MoveComp->MaxWalkSpeed = 330.0f;
	MoveComp->MaxWalkSpeedCrouched = 200.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->TargetArmLength = MaxCameraDistance;
	SpringArm->SetWorldRotation(CameraAngle);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 7.0f;
	SpringArm->CameraRotationLagSpeed = 18.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");
	GrabComp = CreateDefaultSubobject<UGrabber>("Grabber");
	GrabComp->SetupAttachment(GetMesh());

	SetupStimulusSource();
}


// Called when the game starts or when spawned
void ASpyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Controller = Cast<ASpyPlayerController>(GetController());
}

// Called every frame
void ASpyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASpyCharacter::ZoomOut(float Value)
{
	if (0 < Value && SpringArm->TargetArmLength != MinCameraDistance)
	{
		SpringArm->TargetArmLength -= Value;
	}
	else if (0 > Value && SpringArm->TargetArmLength != MaxCameraDistance)
	{
		SpringArm->TargetArmLength -= Value;
	}
}

void ASpyCharacter::Equip(AWeapon* Weapon)
{
	
}

void ASpyCharacter::GrabEnemyBody(UPrimitiveComponent* EnemyMesh)
{
	GrabComp->Grab(EnemyMesh);
}

void ASpyCharacter::ReleaseEnemyBody()
{
	GrabComp->Release();
}

void ASpyCharacter::ThrowGrenade()
{
	if (Grenade != NULL && GrenadeCount != 0)
	{
		GetWorld()->SpawnActor<AActor>(Grenade, GetActorLocation(), GetActorRotation());
		GrenadeCount = GrenadeCount - 1;
	}
}

void ASpyCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Dead. Game Over."));
	if(!bIsDead)
	{
		//DetachFromControllerPendingDestroy();
		Controller->CharacterDeath();
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetMesh()->SetCollisionProfileName(TEXT("RagDoll"));
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
		RemoveStumulusSource();
	}
	//SetLifeSpan(10.0f); // 
}

bool ASpyCharacter::IsDead()
{
	return bIsDead;
}

void ASpyCharacter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());

		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void ASpyCharacter::RemoveStumulusSource()
{
	if (StimulusSource)
	{
		StimulusSource->UnregisterFromPerceptionSystem();
	}
}

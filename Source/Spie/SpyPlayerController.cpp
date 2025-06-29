// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SpyCharacter.h"
#include "Gun.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Pistol_Ammo.h"

ASpyPlayerController::ASpyPlayerController()
{
    bShowMouseCursor = true;
}

void ASpyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ASpyCharacter>(GetCharacter());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		
	}
}

void ASpyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Move);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Zoom);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Crouch);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Interact);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Attack);
		EnhancedInputComponent->BindAction(RotateTriggerAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::SetCameraCanRotate);
		EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::RotateCamera);
		EnhancedInputComponent->BindAction(EquipChangeAction1, ETriggerEvent::Triggered, this, &ASpyPlayerController::EquipChange1);
		EnhancedInputComponent->BindAction(EquipChangeAction2, ETriggerEvent::Triggered, this, &ASpyPlayerController::EquipChange2);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Reload);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &ASpyPlayerController::Throw);
	}
}

void ASpyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	RotateCharacter();
}

void ASpyPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	APawn* const PlayerPawn = GetPawn();
	FVector RightDirection = PlayerPawn->GetComponentByClass<UCameraComponent>()->GetRightVector();
	FVector ForwardDirection = PlayerPawn->GetComponentByClass<UCameraComponent>()->GetForwardVector().RotateAngleAxis(-60.f, RightDirection);
	
	if (PlayerPawn)
	{
		// add movement 
		PlayerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		PlayerPawn->AddMovementInput(RightDirection, MovementVector.X);
	}


}

void ASpyPlayerController::Zoom(const FInputActionValue& Value)
{
	float ZoomValue = Value.Get<float>() * 100.f;

	PlayerCharacter->ZoomOut(ZoomValue);
}

void ASpyPlayerController::Crouch()
{
	if (PlayerCharacter->bIsCrouched)
	{
		PlayerCharacter->UnCrouch();
	}
	else
	{
		PlayerCharacter->Crouch();
	}
}

void ASpyPlayerController::Interact()
{
	TArray<UPrimitiveComponent*> OverlappingComps;
	PlayerCharacter->GetOverlappingComponents(OverlappingComps);
	if (PlayerCharacter->bBodyGrab == true)
	{
		PlayerCharacter->ReleaseEnemyBody();
		return;
	}
	for (UPrimitiveComponent* Comp : OverlappingComps)
	{
		
		//if (Comp->GetName() == "Weapon Pickup") // Equip Weapon
		//{
		//	PlayerCharacter->Equip(Cast<AWeapon>(Comp->GetOwner()));
		//}
		if (Comp->ComponentHasTag(TEXT("Enemy Body"))) //Grab Enemy's Body
		{
			PlayerCharacter->GrabEnemyBody(Comp);
		}
		else if (Comp->ComponentHasTag(TEXT("Pistol Ammo")))
		{
			APistol_Ammo* Ammo = Cast<APistol_Ammo>(Comp->GetOwner());
			Ammo->GetItem(PlayerCharacter);
		}
		
	}
	
}

void ASpyPlayerController::Attack()
{
	if (PlayerCharacter->CurrentWeapon)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_GameTraceChannel1, false, CursorHit);
		PlayerCharacter->CurrentWeapon->ActivateWeapon(CursorHit.Location);

	}
}

void ASpyPlayerController::Reload()
{
	if (PlayerCharacter->CurrentWeapon != nullptr)
	{
		PlayerCharacter->ReloadWeapon();
	}
}

void ASpyPlayerController::Throw()
{
	PlayerCharacter->ThrowGrenade();
}

void ASpyPlayerController::EquipChange1()
{
	PlayerCharacter->ChangeToUnarmed();
}

void ASpyPlayerController::EquipChange2()
{
	PlayerCharacter->ChangeToPistol();

}



void ASpyPlayerController::RotateCharacter()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		APawn* const PlayerPawn = GetPawn();
		if (PlayerPawn)
		{
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(PlayerPawn->GetActorLocation(),
					FVector(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, PlayerPawn->GetActorLocation().Z));
			
			PlayerPawn->SetActorRotation(FMath::RInterpTo(PlayerPawn->GetActorRotation(), LookRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 8.f));//LookRotation 보간함수
			//DrawDebugLine(GetWorld(), PlayerPawn->GetActorLocation(), Hit.ImpactPoint, FColor::Red, false, -1.f);
		}
	}
}

void ASpyPlayerController::SetCameraCanRotate()
{
	if (bCameraRotate)
	{
		bCameraRotate = false;
	}
	else
	{
		bCameraRotate = true;
	}
}

void ASpyPlayerController::RotateCamera(const FInputActionValue& Value)
{
	if (bCameraRotate)
	{
		FVector2D MouseValue = Value.Get<FVector2D>();
		
		PlayerCharacter->GetComponentByClass<USpringArmComponent>()->AddWorldRotation(FRotator(0, MouseValue.Y * CameraSpeed, 0));
		
	}
}

void ASpyPlayerController::CharacterDeath()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->RemoveMappingContext(DefaultMappingContext);
}

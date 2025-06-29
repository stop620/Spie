// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SpyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ASpyCharacter;

/**
 * 
 */
UCLASS()
class SPIE_API ASpyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	ASpyPlayerController();

	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	void Move(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void Crouch();
	void Interact();
	void Attack();
	void Reload();
	void Throw();
	
	void EquipChange1();
	void EquipChange2();

	void RotateCharacter();
	void SetCameraCanRotate();
	void RotateCamera(const FInputActionValue& Value);
	void CharacterDeath();


protected:
	virtual void BeginPlay() override;

private:
	ASpyCharacter* PlayerCharacter;
	bool bCameraRotate = false;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* RotateTriggerAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* CameraRotateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, Category = Inputs)
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, Category = Inputs)
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = Inputs)
	UInputAction* ReloadAction;

	UPROPERTY(EditDefaultsOnly, Category = Inputs)
	UInputAction* EquipChangeAction1;

	UPROPERTY(EditDefaultsOnly, Category = Inputs)
	UInputAction* EquipChangeAction2;

	UPROPERTY(EditDefaultsOnly, Category = Inputs)
	UInputAction* ThrowAction;


	UPROPERTY(EditDefaultsOnly, Category = "Controll")
	float CameraSpeed = 2.0f;
};

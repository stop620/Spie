// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBasePawn.h"

// Sets default values
ACharacterBasePawn::ACharacterBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


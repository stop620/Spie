// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class SPIE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = Components)
	UStaticMeshComponent* FrameMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere, Category = Components)
	UPhysicsConstraintComponent* PhysicsConstraint;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

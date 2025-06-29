// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("Frame");
	FrameMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	DoorMesh->SetupAttachment(RootComponent);

	DoorMesh->SetSimulatePhysics(true);
	DoorMesh->SetAngularDamping(15.f);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraint");
	PhysicsConstraint->SetupAttachment(RootComponent);

	PhysicsConstraint->ComponentName1.ComponentName = FName(DoorMesh->GetName());
	PhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, 45.f);
	PhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.f);
	PhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45.f);
	PhysicsConstraint->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	PhysicsConstraint->SetAngularOrientationDrive(true, false);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



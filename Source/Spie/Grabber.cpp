// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Character.h"
#include "SpyCharacter.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PlayerCharacter = GetOwner<ASpyCharacter>();
	// ...
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = PlayerCharacter->GetMesh()->GetSocketLocation("BodyGrabber");
		PhysicsHandle->SetTargetLocation(TargetLocation);
		
	}
}

void UGrabber::Grab(UPrimitiveComponent* GrabComp)
{
	if (!(GrabComp->ComponentHasTag("Grabbed")))
	{
		UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
		PhysicsHandle->GrabComponentAtLocation(
			GrabComp,
			NAME_None,
			GrabComp->GetSocketLocation("Spine1")
		);
		GrabComp->ComponentTags.Add("Grabbed");
		PlayerCharacter->bBodyGrab = true;
		UE_LOG(LogTemp, Warning, TEXT("Grab!"));
	}
	
}

void UGrabber::Release()
{
	if (PlayerCharacter->bBodyGrab == true)
	{
		UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
		UPrimitiveComponent* GrabbedComp = PhysicsHandle->GetGrabbedComponent();
		GrabbedComp->ComponentTags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
		PlayerCharacter->bBodyGrab = false;
		
		if (PlayerCharacter->ActorHasTag(TEXT("Can Put In")))
		{
			GrabbedComp->GetOwner()->Destroy();

		}
		UE_LOG(LogTemp, Warning, TEXT("Release!"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Handle = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();
	if (Handle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle on Owner"));
		return Handle;
	}
	else
	{
		return Handle;
	}
}
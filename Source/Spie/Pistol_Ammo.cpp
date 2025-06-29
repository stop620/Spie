// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol_Ammo.h"
#include "SpyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APistol_Ammo::APistol_Ammo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AmmoBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Box Mesh"));
	AmmoBoxMesh->SetupAttachment(RootComponent);
	
	BoxCollision->ComponentTags.Add(TEXT("Pistol Ammo"));
}

// Called when the game starts or when spawned
void APistol_Ammo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APistol_Ammo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APistol_Ammo::GetItem(ACharacterBase* Character)
{
	Super::GetItem(Character);
	if (ActorHasTag("Bullet"))
	{
		Character->RemainAmmo += BulletNum;
	}
	else if (ActorHasTag("Grenade"))
	{
		Cast<ASpyCharacter>(Character)->GrenadeCount += BulletNum;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	this->Destroy();
}


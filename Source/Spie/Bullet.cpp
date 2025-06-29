// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "NiagaraComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	RootComponent = Root;*/

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	RootComponent = Root;

	BulletTrail = CreateDefaultSubobject<UNiagaraComponent>("Bullet Trail");
	BulletTrail->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(1.0f);

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


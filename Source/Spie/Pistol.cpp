// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"

APistol::APistol()
{
    Damage = 10.f;
    Range = 300.f;
    BulletSize = 0.5f;
}

void APistol::BeginPlay()
{
    Super::BeginPlay();
}

void APistol::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_PatrolPath.h"

// Sets default values
AAI_PatrolPath::AAI_PatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AAI_PatrolPath::GetPatrolPoint(int const index) const
{
    return PatrolPoints[index];
}

int AAI_PatrolPath::Num() const
{
    return PatrolPoints.Num();
}


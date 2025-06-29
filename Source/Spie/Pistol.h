// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API APistol : public AGun
{
	GENERATED_BODY()
	
public:
	APistol();

protected:
	virtual void BeginPlay() override;

	

public:
	virtual void Tick(float DeltaTime) override;
};

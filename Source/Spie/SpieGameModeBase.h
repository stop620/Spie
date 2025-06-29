// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpieGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API ASpieGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpieGameModeBase();

protected:
	virtual void BeginPlay() override;
	
	FDataTableRowHandle CurrentQuest;

private:
	void LoadCurrentQuest();
};

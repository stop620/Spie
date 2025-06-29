// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpieGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPIE_API USpieGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USpieGameInstance();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	FDataTableRowHandle CurrentQuest;
};

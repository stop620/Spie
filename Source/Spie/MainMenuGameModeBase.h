// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

class UUserWidget;


UCLASS()
class SPIE_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameModeBase();

	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidget;

	UUserWidget* MainMenu;
};

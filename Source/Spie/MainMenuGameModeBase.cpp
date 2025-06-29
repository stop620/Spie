// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
}

void AMainMenuGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    MainMenu = CreateWidget(PC, MainWidget);
    MainMenu->AddToViewport();
}

void AMainMenuGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

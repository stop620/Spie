// Fill out your copyright notice in the Description page of Project Settings.


#include "SpieGameModeBase.h"
#include "SpieGameInstance.h"


ASpieGameModeBase::ASpieGameModeBase()
{
}

void ASpieGameModeBase::BeginPlay()
{
    LoadCurrentQuest();

}

void ASpieGameModeBase::LoadCurrentQuest()
{
    this->CurrentQuest = Cast<USpieGameInstance>(GetGameInstance())->CurrentQuest;

    UE_LOG(LogTemp, Warning, TEXT("Accept Quest Name: &s"), CurrentQuest.RowName);
}

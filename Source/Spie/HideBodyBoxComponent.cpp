// Fill out your copyright notice in the Description page of Project Settings.


#include "HideBodyBoxComponent.h"

UHideBodyBoxComponent::UHideBodyBoxComponent()
{
    OnComponentBeginOverlap.AddDynamic(this, &UHideBodyBoxComponent::OnOverlapBegin);
    OnComponentEndOverlap.AddDynamic(this, &UHideBodyBoxComponent::OnOverlapEnd);

}

void UHideBodyBoxComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    OtherActor->Tags.Add(TEXT("Can Put In"));
}

void UHideBodyBoxComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    OtherActor->Tags.Remove(TEXT("Can Put In"));
}

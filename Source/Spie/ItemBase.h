// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ItemBase.generated.h"

class ACharacterBase;

UCLASS()
class SPIE_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = Components)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, Category = Components)
	UBoxComponent* BoxCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetItem(ACharacterBase* Character);
private:
	

};

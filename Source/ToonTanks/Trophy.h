// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trophy.generated.h"

UCLASS()
class TOONTANKS_API ATrophy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrophy();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	virtual void Destroyed();

};

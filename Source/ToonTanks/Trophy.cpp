// Fill out your copyright notice in the Description page of Project Settings.


#include "Trophy.h"

// Sets default values
ATrophy::ATrophy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh; // Set the static mesh as the root component
}

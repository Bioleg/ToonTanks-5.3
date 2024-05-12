// Fill out your copyright notice in the Description page of Project Settings.


#include "Trophy.h"
#include "MainGameMode.h"

// Sets default values
ATrophy::ATrophy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh; // Set the static mesh as the root component
}

void ATrophy::Destroyed()
{
	AMainGameMode* Gamemode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Gamemode) {
		Gamemode->GameOver(true);
	}
}




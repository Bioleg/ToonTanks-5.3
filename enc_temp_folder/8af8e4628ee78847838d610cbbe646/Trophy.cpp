// Fill out your copyright notice in the Description page of Project Settings.


#include "Trophy.h"

// Sets default values
ATrophy::ATrophy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrophy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrophy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


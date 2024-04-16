// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find the distance to the Tank
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// Check to see if the tank is in range
		if (Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}
		// If in range, rotate turret toward tank
	}
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
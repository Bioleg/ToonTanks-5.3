// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tank.h"

void ATurretAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

bool ATurretAIController::IsDead() const
{
	ATank* ControllerCharacter = Cast<ATank>(GetPawn());
	if (ControllerCharacter)
	{
		return ControllerCharacter->bIsDead;
	}

	return true;
}

void ATurretAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviour)
	{
		RunBehaviorTree(AIBehaviour);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Tank.h"

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
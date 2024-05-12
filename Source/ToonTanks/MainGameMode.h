// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UPROPERTY(BlueprintReadOnly)
	int32 TowersDifference = 0;

	UPROPERTY(BlueprintReadWrite)
	float Time = 0;


protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:

	class ATank* Tank;
	class AMainPlayerController* MainPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TowersAmount = 0;
	int32 GetTargetTowerCount();

	float PlayerHealth;
};

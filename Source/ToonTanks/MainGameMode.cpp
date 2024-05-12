// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "Trophy.h"
#include "MainPlayerController.h"

void AMainGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if (MainPlayerController)
        {

            MainPlayerController->SetPlayerEnabledState(false);
            
        }

        GameOver(false); // The player loses

    }
    else if (ATurret* DestroyedTower = Cast<ATurret>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TowersDifference = TowersAmount - GetTargetTowerCount();
        UE_LOG(LogTemp, Display, TEXT("%i"), TowersDifference);
    }
    else if (ATrophy* DestroyedTrophy = Cast<ATrophy>(DeadActor))
    {
        DestroyedTrophy->Destroy();
        GameOver(false);
    }
}

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AMainGameMode::HandleGameStart()
{
    TowersAmount = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    StartGame();

    if (MainPlayerController)
    {
        MainPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            MainPlayerController,
            &AMainPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
}

int32 AMainGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;

    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Towers);

    return Towers.Num();
}

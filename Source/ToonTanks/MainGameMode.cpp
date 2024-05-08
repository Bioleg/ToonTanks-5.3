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

        /*--TargetTowers;
        if (TargetTowers == 0)
        {
            GameOver(true);
        }*/
    }
    else if (ATrophy* DestroyedTrophy = Cast<ATrophy>(DeadActor))
    {
        Tank->HandleDestruction();
        if (MainPlayerController)
        {
            MainPlayerController->SetPlayerEnabledState(false);

        }
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
    //TargetTowers = GetTargetTowerCount();
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

//int32 AMainGameMode::GetTargetTowerCount()
//{
//    TArray<AActor*> Towers;
//
//    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Towers);
//
//    return Towers.Num();
//}

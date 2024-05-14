// Fill out your copyright notice in the Description page of Project Settings.


#include "Catapult.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "MainPlayerController.h"

// Sets default values
ACatapult::ACatapult()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));

}

void ACatapult::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACatapult::OnCatapultBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACatapult::OnCatapultEndOverlap);
}

void ACatapult::OnCatapultBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Hello there"));

    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(this, &ACatapult::Launch, OtherActor);
    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, TimeDelay, false);
	bDoLaunch = true;
}

void ACatapult::OnCatapultEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("Byeee"));
	bDoLaunch = false;
}

void ACatapult::Launch(class AActor* OtherActor)
{
	if (bDoLaunch)
	{
		UE_LOG(LogTemp, Display, TEXT("Launching!"));
	}
}


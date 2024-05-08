// Fill out your copyright notice in the Description page of Project Settings.


#include "TrophyTriggerBox.h"
#include "Tank.h"
#include "MainGameMode.h"

ATrophyTriggerBox::ATrophyTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ATrophyTriggerBox::OnComponentBeginOverlap);
}

void ATrophyTriggerBox::OnComponentBeginOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{

	ATank* Tank = Cast<ATank>(OtherActor);
	if (Tank)
	{
		if (OtherActor == Tank)
		{
			if (Tank->bHasTrophy)
			{
				AMainGameMode* Gamemode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
				Gamemode->GameOver(true);
			}
		}
		
	}

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TrophyTriggerBox.h"

ATrophyTriggerBox::ATrophyTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ATrophyTriggerBox::OnComponentBeginOverlap);
}

void ATrophyTriggerBox::OnComponentBeginOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		UE_LOG(LogTemp, Display, TEXT("Hello player dear"));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TrophyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATrophyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:

	ATrophyTriggerBox();
	
private:

	UFUNCTION()
	void OnComponentBeginOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
};

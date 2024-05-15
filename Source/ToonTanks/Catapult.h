// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Catapult.generated.h"

UCLASS()
class TOONTANKS_API ACatapult : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACatapult();

	virtual void BeginPlay();

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnCatapultBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnCatapultEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		);

	class AMainPlayerController* MainPlayerController;

	UPROPERTY(EditDefaultsOnly)
	float TimeDelay;

	UFUNCTION()
	void Launch(class AActor* OtherActor);

	void TellBasePawnToDisablePhysicsOnLanding(AActor* OtherActor, class UCapsuleComponent* CatapultCaps);

	UPROPERTY()
	bool bDoLaunch = false;

};

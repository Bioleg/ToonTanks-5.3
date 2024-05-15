// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles && DeathSound && DeathCameraShakeClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->
			GetComponentRotation(), 
			LookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			TurretRotationSpeed
		));
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

}

void ABasePawn::DisablePhysicsOnLanding(class AActor* OtherActor, class UCapsuleComponent* CatapultCaps)
{
	UE_LOG(LogTemp, Display, TEXT("Trying to disable physics Launching!"));
	if (floor(OtherActor->GetActorLocation().Z) != 94 || floor(OtherActor->GetActorLocation().Z == 100))
	{
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(this, &ABasePawn::DisablePhysicsOnLanding, OtherActor, CatapultCaps);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, 1.f, false);
	}
	if (floor(OtherActor->GetActorLocation().Z) == 94)
	{

		UE_LOG(LogTemp, Display, TEXT("Disabling physics Launching!"));
		CatapultCaps->SetSimulatePhysics(false);
		FVector ActorLocation(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, 100);
		FRotator ActorRotation(0, OtherActor->GetActorRotation().Yaw, OtherActor->GetActorRotation().Roll);

		OtherActor->SetActorLocation(ActorLocation);
		OtherActor->SetActorRotation(ActorRotation);
	}
}
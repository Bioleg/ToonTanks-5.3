// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ATank::ATank() 
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	TrophyAttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Trophy Attachement Point"));
	TrophyAttachmentPoint->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &ATank::AttachTrophy);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call the parent version

	// Get the player controller
	auto playerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(inputMapping, 0);

	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	playerEIcomponent->BindAction(inputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
	playerEIcomponent->BindAction(inputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
	playerEIcomponent->BindAction(inputFire, ETriggerEvent::Started, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime) 
{

	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;

		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	bIsHidden = true;
	SetActorTickEnabled(false);
}


void ATank::BeginPlay() 
{
	Super::BeginPlay();

	bIsHidden = false;
	bIsDead = true;

	TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::Move(const FInputActionValue & Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaLocation.X = Value.Get<float>() * Speed * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const FInputActionValue& Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value.Get<float>() * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::AttachTrophy(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Trophy") && TrophyAttachmentPoint && OtherActor)
	{
		OtherActor->AttachToComponent(TrophyAttachmentPoint, FAttachmentTransformRules::KeepRelativeTransform);

		OtherActor->SetActorRelativeLocation(FVector::ZeroVector);
		
		bHasTrophy = true;
	}
}

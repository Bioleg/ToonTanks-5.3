// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "D:/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "D:/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "D:/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "D:/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

ATank::ATank() 
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
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

	//Bind Move() to the mapping
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down".
	playerEIcomponent->BindAction(inputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
	playerEIcomponent->BindAction(inputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
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

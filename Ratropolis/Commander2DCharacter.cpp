// Fill out your copyright notice in the Description page of Project Settings.


#include "Commander2DCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Game/BasePlayerState.h"
#include "Interrupt/PlayerInteractComponent.h"


// Sets default values
ACommander2DCharacter::ACommander2DCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	
	PlayerInteractComponent1 = CreateDefaultSubobject<UPlayerInteractComponent>("InteractComponent1");
}

// Called when the game starts or when spawned
void ACommander2DCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void ACommander2DCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACommander2DCharacter::Move);
		EnhancedInputComponent->BindAction(InteractAction1, ETriggerEvent::Triggered, this, &ACommander2DCharacter::InteractKey1);
		EnhancedInputComponent->BindAction(InteractAction2, ETriggerEvent::Triggered, this, &ACommander2DCharacter::InteractKey2);
	}
}

void ACommander2DCharacter::InteractKey1()
{
	if (PlayerInteractComponent1)
	{
		if (ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>())
		{
			if (BasePlayerState->GetGold() >= 10)
			{
				BasePlayerState->AddedGold(-10);
				PlayerInteractComponent1->DoInteract1();
			}
		}
	}
}

void ACommander2DCharacter::InteractKey2()
{
	if (PlayerInteractComponent1)
	{
		if (ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>())
		{
			if (BasePlayerState->GetGold() >= 10)
			{
				BasePlayerState->AddedGold(-10);
				PlayerInteractComponent1->DoInteract2();
			}
		}
	}
}

void ACommander2DCharacter::Move(const FInputActionValue& Value)
{
	const float MovementValue = Value.Get<float>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementValue);
	}
}


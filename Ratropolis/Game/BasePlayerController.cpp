// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"


inline void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (PlayerHUDClass)
		{
			PlayerHUDInstance = CreateWidget<UUserWidget>(this, PlayerHUDClass);

			if (PlayerHUDInstance)
			{
				PlayerHUDInstance->AddToViewport();
			}
		}
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}



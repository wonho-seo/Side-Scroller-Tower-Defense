// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Practice/Ratropolis/BaseGASActor.h"
#include "BaseAttackBuilding.generated.h"

UCLASS()
class PRACTICE_API ABaseAttackBuilding : public ABaseGASActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseAttackBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

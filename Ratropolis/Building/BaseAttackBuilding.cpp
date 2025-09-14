// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttackBuilding.h"

#include "Practice/Ratropolis/GAS/TowerAttributeSet.h"


// Sets default values
ABaseAttackBuilding::ABaseAttackBuilding()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AttributeSet = CreateDefaultSubobject<UTowerAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void ABaseAttackBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAttackBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseAttackBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResoureBuilding.h"

#include "Practice/Ratropolis/GAS/TowerAttributeSet.h"


// Sets default values
ABaseResourceBuilding::ABaseResourceBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AttributeSet = CreateDefaultSubobject<UTowerAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void ABaseResourceBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseResourceBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableAreaVolume.h"

#include "BaseAttackBuilding.h"
#include "BaseResoureBuilding.h"
#include "Components/BoxComponent.h"


// Sets default values
ABuildableAreaVolume::ABuildableAreaVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;
	
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));

	SpawnVolume->SetupAttachment(RootComponent);
	SpawnVolume->SetBoxExtent(FVector(50.f, 100.f, 100.f));
	SpawnVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpawnVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpawnVolume->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	SpawnVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABuildableAreaVolume::CreateAttackTower()
{
	if (bIsActive)
	{
		bIsActive = false;

		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Y = 0;
		GetWorld()->SpawnActor<ABaseAttackBuilding>(AttackBuildingClass, SpawnLocation, GetActorRotation());
	}
}

void ABuildableAreaVolume::CreateResourceTower()
{
	if (bIsActive)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Y = 0;
		GetWorld()->SpawnActor<ABaseResourceBuilding>(ResourceBuildingClass, SpawnLocation, GetActorRotation());
		bIsActive = false;
	}
}

void ABuildableAreaVolume::Interact1_Implementation()
{
	CreateAttackTower();
}

void ABuildableAreaVolume::Interact2_Implementation()
{
	CreateResourceTower();
}


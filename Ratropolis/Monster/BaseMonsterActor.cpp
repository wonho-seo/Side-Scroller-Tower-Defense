// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonsterActor.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Practice/Ratropolis/GAS/TowerAttributeSet.h"
#include "Practice/Ratropolis/GAS/AttributeSet/MonsterAttributeSet.h"


// Sets default values
ABaseMonsterActor::ABaseMonsterActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = 100.f;
	}

	AttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void ABaseMonsterActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseMonsterActor::OnBreakChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::OnBreakChanged(CallbackTag, NewCount);
	if (NewCount > 0)
	{
		Destroy();
	}
}

// Called every frame
void ABaseMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


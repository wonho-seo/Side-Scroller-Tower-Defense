// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Practice/Ratropolis/BaseGASActor.h"
#include "BaseMonsterActor.generated.h"

struct FGameplayTag;
class UWidgetComponent;
class UBoxComponent;
class UFloatingPawnMovement;
class UGameplayAbility;
class UAttributeSet;

UCLASS()
class PRACTICE_API ABaseMonsterActor : public ABaseGASActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseMonsterActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	virtual void OnBreakChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

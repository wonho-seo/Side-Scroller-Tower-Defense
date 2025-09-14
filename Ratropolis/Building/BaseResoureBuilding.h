// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Practice/Ratropolis/BaseGASActor.h"
#include "BaseResoureBuilding.generated.h"

UCLASS()
class PRACTICE_API ABaseResourceBuilding : public ABaseGASActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseResourceBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 Level;
	
};

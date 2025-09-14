// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Practice/Ratropolis/Interrupt/InteractInterface.h"
#include "BuildableAreaVolume.generated.h"

class ABaseResourceBuilding;
class ABaseAttackBuilding;
class UBoxComponent;

UCLASS()
class PRACTICE_API ABuildableAreaVolume : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildableAreaVolume();

	UFUNCTION(BlueprintCallable)
	void CreateAttackTower();
	
	UFUNCTION(BlueprintCallable)
	void CreateResourceTower();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> SpawnVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn")
	TSubclassOf<ABaseAttackBuilding> AttackBuildingClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn")
	TSubclassOf<ABaseResourceBuilding> ResourceBuildingClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn")
	bool bIsActive = true;

	// interact
	virtual void Interact1_Implementation() override;
	virtual void Interact2_Implementation() override;
};

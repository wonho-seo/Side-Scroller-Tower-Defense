// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractComponent.generated.h"


class USphereComponent;
class UInputAction;
class IInteractInterface;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PRACTICE_API UPlayerInteractComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPlayerInteractComponent();

	UFUNCTION(BlueprintCallable)
	void UpdateCurrentInteractInterface();
	
	[[nodiscard]] FORCEINLINE TScriptInterface<IInteractInterface> GetCurrentInteractInterface() const
	{
		return CurrentInteractInterface;
	}

	void SetCurrentInteractInterface(const TScriptInterface<IInteractInterface>& InCurrentInteractInterface)
	{
		this->CurrentInteractInterface = InCurrentInteractInterface;
	}
	
	UFUNCTION()
	void DoInteract1();
	UFUNCTION()
	void DoInteract2();
	
protected:
	
	UFUNCTION()
	void OnBuildingOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBuildingOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interrupt")
	TObjectPtr<USphereComponent> InterruptCollision;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Interrupt")
	TArray<TScriptInterface<IInteractInterface>> OverlappingInteractInterfaces;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Interrupt")
	TScriptInterface<IInteractInterface> CurrentInteractInterface;
	
public:


private:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AActor> Owner;

	UPROPERTY()
	FTimerHandle DistanceCheckTimer;
};

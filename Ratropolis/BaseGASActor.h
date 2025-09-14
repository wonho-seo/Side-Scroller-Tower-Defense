// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Practice/Ratropolis/Interrupt/InteractInterface.h"
#include "BaseGASActor.generated.h"

class UBaseAttributeSet;
class UHPBarWidget;
class UWidgetComponent;
struct FOnAttributeChangeData;
class UBoxComponent;
class UTowerAttributeSet;
class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class USphereComponent;

UCLASS()
class PRACTICE_API ABaseGASActor : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGASActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USceneComponent> SceneComponent ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UBoxComponent> CollisionComponent;
	
	//UI
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> HealthBarComponent;
	
	// GAS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultStatsEffect;
	
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnBreakChanged(const FGameplayTag CallbackTag, int32 NewCount);
private:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void SetupDefaultAbilities();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

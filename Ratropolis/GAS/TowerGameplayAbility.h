// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TowerGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UTowerGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTowerGameplayAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
	TSubclassOf<UGameplayEffect> PassiveEffect;
};

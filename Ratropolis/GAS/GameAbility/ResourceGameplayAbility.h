// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ResourceGameplayAbility.generated.h"

class UAbilityTask_WaitDelay;
/**
 * 
 */
UCLASS()
class PRACTICE_API UResourceGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> AddGoldEffectClass;

	UFUNCTION()
	void OnDelayFinished();

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> WaitDelayTask;

private:
	bool CreateResourceLoop();
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerGameplayAbility.h"

#include "AbilitySystemComponent.h"

UTowerGameplayAbility::UTowerGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTowerGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
	{
		if (PassiveEffect)
		{
			FGameplayEffectSpecHandle EffectsSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(PassiveEffect, 1, AbilitySystemComponent->MakeEffectContext());
			if (EffectsSpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectsSpecHandle);
				EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
				
				return;
			}
		}
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	
}

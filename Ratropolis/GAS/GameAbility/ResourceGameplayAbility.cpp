// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceGameplayAbility.h"

#include "Practice/Ratropolis/GAS/TowerAttributeSet.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Kismet/GameplayStatics.h"
#include "Practice/Ratropolis/Core/CustomGameplayTag.h"
#include "Practice/Ratropolis/Game/BasePlayerState.h"

void UResourceGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!CreateResourceLoop())
	{

		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}
}

void UResourceGameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (WaitDelayTask)
	{
		WaitDelayTask->EndTask();
	}
}

void UResourceGameplayAbility::OnDelayFinished()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PlayerController) 
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
		return;
	}
	
	if (ABasePlayerState* PlayerState = PlayerController->GetPlayerState<ABasePlayerState>())
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent())
		{
			if (GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(Actor_States_Break))
			{
				CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
				return;
			}
			
			if (const UTowerAttributeSet* AttributeSet = GetAbilitySystemComponentFromActorInfo()->GetSet<UTowerAttributeSet>())
			{
				const float GoldToAdd =  AttributeSet->GetResourceGenerationRate();

				FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AddGoldEffectClass, GetAbilityLevel());
				EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("Data.GoldAmount")), GoldToAdd);

				if (AbilitySystemComponent && EffectSpecHandle.IsValid())
				{
					AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
				}
			}
		}
	}
	if (!CreateResourceLoop())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true);
	}

}

bool UResourceGameplayAbility::CreateResourceLoop()
{
	if (const UTowerAttributeSet* AttributeSet = GetAbilitySystemComponentFromActorInfo()->GetSet<UTowerAttributeSet>())
	{
		const float GenerationFrequency = AttributeSet->GetAttackSpeed() > 0 ? AttributeSet->GetAttackSpeed() : 1.f;

		const float Delay = 1.0f / GenerationFrequency;

		WaitDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, Delay);
		if (WaitDelayTask)
		{
			WaitDelayTask->OnFinish.AddDynamic(this, &UResourceGameplayAbility::OnDelayFinished);
			WaitDelayTask->ReadyForActivation();
			return true;
		}
	}
	return false;
}

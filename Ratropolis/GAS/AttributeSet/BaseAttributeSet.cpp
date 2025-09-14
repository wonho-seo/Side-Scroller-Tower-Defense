// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Practice/Ratropolis/Core/CustomGameplayTag.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	MaxHealth = 100.f;
	Health = 100.f;
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float CurrentHealth = GetHealth();

		if (CurrentHealth <= 0.f)
		{
			if (UAbilitySystemComponent* AbilitySystemComponent = &Data.Target)
			{
				AbilitySystemComponent->AddLooseGameplayTag(Actor_States_Break);
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

#include "AbilitySystemComponent.h"
#include "../GAS/AttributeSet/PlayerAttributeSet.h"
#include "Practice/Ratropolis/GAS/AttributeSet/PlayerAttributeSet.h"

ABasePlayerState::ABasePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

int32 ABasePlayerState::GetGold() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetGold();
	}
	return 0;
}

void ABasePlayerState::AddedGold(const int32 InAddedGold)
{
	if (AttributeSet)
	{
		AttributeSet->SetGold(AttributeSet->GetGold() + InAddedGold);
	}
}

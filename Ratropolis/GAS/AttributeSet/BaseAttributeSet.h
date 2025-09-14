// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributeSet, Health)
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributeSet, AttackPower)
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributeSet, AttackSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData AttackPower;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData AttackSpeed;
	
};

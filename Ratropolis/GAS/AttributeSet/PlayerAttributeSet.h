// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, Gold)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Gold = 10;
};

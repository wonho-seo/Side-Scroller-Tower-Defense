// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSet/BaseAttributeSet.h"
#include "TowerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UTowerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS_BASIC(UTowerAttributeSet, ResourceGenerationRate)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData ResourceGenerationRate;
	
};

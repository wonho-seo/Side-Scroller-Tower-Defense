// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (APawn* ControlledPawn = AIController->GetPawn())
		{
			if (UAbilitySystemComponent* AbilitySystemComponent = ControlledPawn->FindComponentByClass<UAbilitySystemComponent>())
			{
				AbilitySystemComponent->TryActivateAbilityByClass(AttackAbility);
				if (SuperResult == EBTNodeResult::Succeeded)
				{
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}

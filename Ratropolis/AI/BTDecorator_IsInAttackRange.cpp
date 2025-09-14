// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool SuperResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey())))
		{
			return SuperResult && FVector::DistSquared2D(OwnerActor->GetActorLocation(), TargetActor->GetActorLocation()) < AttackRange * AttackRange;
		}
	}
	return false;
}

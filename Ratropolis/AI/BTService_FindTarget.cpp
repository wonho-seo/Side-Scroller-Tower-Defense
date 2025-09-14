// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("Find Target");

	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		
		FVector StartLocation = OwnerPawn->GetActorLocation();
		FVector EndLocation = StartLocation + (OwnerPawn->GetActorForwardVector() * SearchRange);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(OwnerPawn);

		FHitResult HitResult;

		// Multi 대신 Single 함수를 사용합니다.
		bool bHasHit = UKismetSystemLibrary::BoxTraceSingleForObjects(
			GetWorld(),
			StartLocation,
			EndLocation,
			SearchSize,
			OwnerPawn->GetActorRotation(),
			ObjectTypes,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true
		);

		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

		if (bHasHit)
		{
			BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), HitResult.GetActor());
		}
		else
		{
			BlackboardComp->ClearValue(GetSelectedBlackboardKey());
		}
	}
}

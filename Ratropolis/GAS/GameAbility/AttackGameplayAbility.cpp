// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Practice/Ratropolis/BaseGASActor.h"
#include "Practice/Ratropolis/Core/CustomGameplayTag.h"

void UAttackGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(Actor_States_Break))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	
	FVector StartLocation = AvatarActor->GetActorLocation();
	FVector EndLocation = StartLocation + (AvatarActor->GetActorForwardVector() * AttackRange.X);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AvatarActor);

	TArray<FHitResult> HitResults;

	UKismetSystemLibrary::BoxTraceMulti(
		this,
		StartLocation,
		EndLocation,
		FVector(0.f, AttackRange.Y, AttackRange.Z),
		AvatarActor->GetActorRotation(),
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true);

	TArray<TWeakObjectPtr<AActor>> TargetActors; // 유효한 타겟 액터들을 담을 배열
	for (const FHitResult& Hit : HitResults)
	{
		if (ABaseGASActor* TargetActor = Cast<ABaseGASActor>(Hit.GetActor()))
		{
			TargetActors.Add(TargetActor);
		}
	}

	if (TargetActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
        
		TargetData->TargetActorArray.Append(TargetActors);

		FGameplayAbilityTargetDataHandle TargetDataHandle(TargetData);

		FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());
		if (DamageSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo, DamageSpecHandle, TargetDataHandle);
		}
	}

	if (CooldownEffectClass)
	{
		ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	}
    
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

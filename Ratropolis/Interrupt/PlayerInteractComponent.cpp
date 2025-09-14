// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractComponent.h"
#include "Components/SphereComponent.h"


void UPlayerInteractComponent::UpdateCurrentInteractInterface()
{
	CurrentInteractInterface = nullptr;
	float MinRange = TNumericLimits<float>::Max();
	for (auto InteractInterface : OverlappingInteractInterfaces)
	{
		if (AActor* InteractActor = Cast<AActor>(InteractInterface.GetObjectRef()))
		{
			float CurrentDistance = FVector::Dist(GetOwner()->GetActorLocation(), InteractActor->GetActorLocation());
			if (CurrentDistance < MinRange)
			{
				CurrentInteractInterface = InteractInterface;
				MinRange = CurrentDistance;
			}
		}
	}
}

void UPlayerInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (Owner)
	{
		InterruptCollision->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	}

}

// Sets default values for this component's properties
UPlayerInteractComponent::UPlayerInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InterruptCollision = CreateDefaultSubobject<USphereComponent>(FName("Collision"));
	InterruptCollision->SetSphereRadius(500.f);
	InterruptCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InterruptCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InterruptCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InterruptCollision->SetCollisionObjectType(ECC_Pawn);
	
	InterruptCollision->OnComponentBeginOverlap.AddDynamic(this, &UPlayerInteractComponent::OnBuildingOverlapBegin);
	InterruptCollision->OnComponentEndOverlap.AddDynamic(this, &UPlayerInteractComponent::OnBuildingOverlapEnd);
	
	// ...
}

void UPlayerInteractComponent::DoInteract1()
{
	if (CurrentInteractInterface)
	{
		IInteractInterface::Execute_Interact1(CurrentInteractInterface.GetObjectRef());
	}
}

void UPlayerInteractComponent::DoInteract2()
{
	if (CurrentInteractInterface)
	{
		IInteractInterface::Execute_Interact2(CurrentInteractInterface.GetObject());
	}
}

// Interrupt
void UPlayerInteractComponent::OnBuildingOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TScriptInterface<IInteractInterface> InteractInterface = OtherActor)
	{
		OverlappingInteractInterfaces.AddUnique(InteractInterface);
		
		if (OverlappingInteractInterfaces.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("ABCD"));

			if (!GetWorld()->GetTimerManager().IsTimerActive(DistanceCheckTimer))
			{
				GetWorld()->GetTimerManager().SetTimer(DistanceCheckTimer, this, &UPlayerInteractComponent::UpdateCurrentInteractInterface, 0.1f, true);
			}
		}
	}

}

void UPlayerInteractComponent::OnBuildingOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (TScriptInterface<IInteractInterface> InteractInterface = OtherActor)
	{
		OverlappingInteractInterfaces.Remove(InteractInterface);
		UpdateCurrentInteractInterface();
		
		if (OverlappingInteractInterfaces.Num() <= 1)
		{
			GetWorld()->GetTimerManager().ClearTimer(DistanceCheckTimer);
		}
	}
}



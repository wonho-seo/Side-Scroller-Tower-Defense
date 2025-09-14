// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGASActor.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Practice/Ratropolis/Core/CustomGameplayTag.h"
#include "Practice/Ratropolis/GAS/TowerAttributeSet.h"
#include "Practice/Ratropolis/UI/HPBarWidget.h"


// Sets default values
ABaseGASActor::ABaseGASActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(SceneComponent);
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionComponent->SetupAttachment(SceneComponent);
	CollisionComponent->SetCollisionObjectType(ECC_Pawn);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	// UI
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(RootComponent);
	
	// GAS
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void ABaseGASActor::BeginPlay()
{
	Super::BeginPlay();

	SetupDefaultAbilities();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ABaseGASActor::OnHealthChanged);
		AbilitySystemComponent->RegisterGameplayTagEvent(Actor_States_Break, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ABaseGASActor::OnBreakChanged);
	}
}

void ABaseGASActor::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (HealthBarComponent)
	{
		if (UHPBarWidget* HealthBar = Cast<UHPBarWidget>(HealthBarComponent->GetUserWidgetObject()))
		{
			HealthBar->UpdateHealthPercent(Data.NewValue, AttributeSet->GetMaxHealth());
		}
	}
}

void ABaseGASActor::OnBreakChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		if (AController* AIController = GetController())
		{
			AIController->UnPossess();
		}

		if (CollisionComponent)
		{
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		}
	}
}

UAbilitySystemComponent* ABaseGASActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseGASActor::SetupDefaultAbilities()
{
	if (AbilitySystemComponent)
	{
		if (DefaultStatsEffect)
		{
			FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultStatsEffect, 1, ContextHandle);

			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
		for (auto& AbilityClass : DefaultAbilities)
		{
			if (AbilityClass)
			{
				FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, -1, this);
				FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
				AbilitySystemComponent->TryActivateAbility(AbilitySpecHandle);
				
			}
		}
	}
}

// Called every frame
void ABaseGASActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


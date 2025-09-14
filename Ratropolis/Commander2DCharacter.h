// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Commander2DCharacter.generated.h"

class UPlayerInteractComponent;
class USphereComponent;
class IInteractInterface;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class PRACTICE_API ACommander2DCharacter : public ACharacter
{
	GENERATED_BODY()

	//mesh
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	// movement
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
private:
	void Move(const FInputActionValue& Value);
	
	// interrupt
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "interrupt")
	TObjectPtr<UPlayerInteractComponent> PlayerInteractComponent1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interrupt")
	TObjectPtr<UInputAction> InteractAction1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interrupt")
	TObjectPtr<UInputAction> InteractAction2;

private:
	UFUNCTION()
	void InteractKey1();
	
	UFUNCTION()
	void InteractKey2();
	
public:
	// Sets default values for this character's properties
	ACommander2DCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

// Forward decleration
class UTankBarrel; 
class UTankTurretComponent;

// Holds 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

	void SetTankComponentsReference(UTankBarrel* BarrelToSet, UTankTurretComponent* TurretToSet );

	// TODO Add set turret reference

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurretComponent* Turret = nullptr;

	void MoveTurretAndBarrelTowards(FVector AimDirection);
	
};

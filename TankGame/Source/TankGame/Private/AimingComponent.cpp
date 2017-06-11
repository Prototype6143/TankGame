// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankTurretComponent.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAimingComponent::SetTankComponentsReference(UTankBarrel* BarrelToSet, UTankTurretComponent* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation,
		HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,	TArray<AActor*>(), false);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found!"), Time);
		MoveTurretAndBarrelTowards(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No Aim solution found"), Time);
	}
}

void UAimingComponent::MoveTurretAndBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotator;

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto TurretDeltaRotator = AimAsRotator - TurretRotator;

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	Turret->RotateTurret(TurretDeltaRotator.Yaw);
}


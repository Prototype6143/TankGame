// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"

void UTankTurretComponent::RotateTurret(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// Given a max Rotation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

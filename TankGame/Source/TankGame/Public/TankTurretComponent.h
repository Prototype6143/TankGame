// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collsiion"))
class TANKGAME_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

	void RotateTurret(float RelativeSpeed);
	
};

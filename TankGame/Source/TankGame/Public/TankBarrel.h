// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collsiion"))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 
	// -1 is max downward movevement, + 1 is upward  movement
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

	// Minimum elevation rotation
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;

	// Maximum elevation rotation
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 30;
};

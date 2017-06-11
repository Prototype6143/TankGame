// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	float CrosshairYLocation = 0.4;

	ATank* GetControlledTank() const;

private:
	UPROPERTY(EditAnywhere, Category = "Aim")
	float LineTraceRange = 1000000;
	
	//  Called when the game starts or when spawned
	void BeginPlay() override;

	// Caled every frame
	virtual void Tick(float DeltaTime) override;

	// start the tank moving the turret and the barrel towards the crosshair
	void AimTowardsCrosshair();

	// return and out parameter, true i fhit landscape
	bool GetSightRayHitLocation( FVector&  OutLocation) const;

	bool GetlookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation( FVector LookDirection, FVector& HitLocation) const;

};

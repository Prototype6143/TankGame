// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller is not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller is posessing = %s"), *(ControlledTank->GetName()));
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has a side affect, is going to 
	{
		if (HitLocation != FVector(0))
		{
			GetControlledTank()->AimAt(HitLocation);
		}
	}
}


// get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation) const
{
	// find crosshair position
	int32 ViewportSizeX, ViewportSizeY;	
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	// Deproject the screen position to a world direction
	FVector LookDirection;
	if (GetlookDirection(ScreenLocation, LookDirection))
	{
		// line trace along that direction, and see what we hit
		GetLookVectorHitLocation( LookDirection, HitLocation );
	}
	return true;
}


bool ATankPlayerController::GetlookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	
	FVector CameraWorldLocation; // TO be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FCollisionQueryParams TraceParams(FName(TEXT("Hit Trace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility, 
		TraceParams)
		)
	{
		HitLocation = HitResult.Location;
		DrawDebugSphere(
			GetWorld(),
			HitResult.Location,
			24,
			32,
			FColor(255, 0, 0)
		);
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

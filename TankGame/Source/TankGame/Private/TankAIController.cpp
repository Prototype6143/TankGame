// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetContolledTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player = %s"), *(PlayerTank->GetName()));
	}

}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetContolledTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

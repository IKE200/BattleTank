// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto TankAI = GetControlledTank();
	
	if (!TankAI)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController is missing a Tank to control!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController for Tank: %s"), *TankAI->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


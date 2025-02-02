// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController is missing a Player Tank to target!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found Player Tank: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetPlayerTank())
	{
		AimTowardsPlayer();
	}
}

void ATankAIController::AimTowardsPlayer() const
{
	ATank* PlayerTank = GetPlayerTank();
	FVector PlayerLocation = PlayerTank->GetActorLocation();
	GetControlledTank()->AimAt(PlayerLocation);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Player) { return nullptr; }
		return Cast<ATank>(Player);
}


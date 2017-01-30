// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto PossesedTank = GetControlledTank();
	if (!PossesedTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is missing a Tank to control"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Player Tank is:  %s"), *PossesedTank->GetName());
	}

}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"), *HitLocation.ToString());
		// TODO Point Barrel towards the hitlocation
	}
}

// Raycast through Crosshair and check where it hits first
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrossHairScreenLocation = FVector2D(ViewportSizeX*CrossHairXRelativeLocation, ViewportSizeY*CrossHairYRelativeLocation);
	// Get Direction from Position
	// Raycast along that direction, see what we hit
	return true;
}

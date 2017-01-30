// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
		GetControlledTank()->AimAt(HitLocation);
		// TODO Point Barrel towards the hitlocation
	}
}

// Raycast through Crosshair and check where it hits first
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrossHairScreenLocation = FVector2D
	(
		ViewportSizeX*CrossHairXRelativeLocation, 
		ViewportSizeY*CrossHairYRelativeLocation
	);

	// Get Direction from Position
	FVector CrossHairWorldDirection;
	if (GetLookDirection(CrossHairScreenLocation, CrossHairWorldDirection))
	{
		if (GetLookVectorHitLocation(HitLocation, CrossHairWorldDirection))
		{
		}
		else
		{
		}
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrossHairScreenLocation, FVector& CrossHairWorldDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld
	(
		CrossHairScreenLocation.X,
		CrossHairScreenLocation.Y,
		CameraWorldLocation,
		CrossHairWorldDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector CrossHairWorldDirection) const
{
	FHitResult Hit;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		StartLocation,
		StartLocation + CrossHairWorldDirection*TankRange,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = Hit.Location;
		return true;
	}
	else
	{
		return false;
	}
}

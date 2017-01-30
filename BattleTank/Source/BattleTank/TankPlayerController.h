// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D CrossHairScreenLocation, FVector& CrossHairWorldDirection) const;
	bool GetLookVectorHitLocation(FVector& HitLocation, FVector CrossHairWorldDirection) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXRelativeLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairYRelativeLocation = 0.33333333;

	UPROPERTY(EditAnywhere)
		float TankRange = 1000000;
	
};

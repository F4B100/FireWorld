// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "FWPlayerCameraManagerFP.generated.h"

/**
 * 
 */
UCLASS()
class FIREWORLD_API AFWPlayerCameraManagerFP : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CrouchInterpolateDuration = 0.2f;
	float CrouchInterpolateTime = 0.0f;
	
	AFWPlayerCameraManagerFP();
	
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};

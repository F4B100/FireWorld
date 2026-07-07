// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "FWPlayerCameraManagerFP.generated.h"

class AFWCharacter;
/**
 * 
 */
UCLASS()
class FIREWORLD_API AFWPlayerCameraManagerFP : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CrouchInterpolateDuration = 0.2f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ViewBoobingMagntude = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ViewBoobingSpeed = 1.5f;

	float CrouchInterpolateTime = 0.0f;
	float ViewBoobingInterpolateTime = 0.0f;

	AFWPlayerCameraManagerFP();
	
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};

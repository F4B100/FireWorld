// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PlayerInfoWidget.generated.h"

class AFWCharacter;
class UPlayerStatWidget;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UPlayerInfoWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UPlayerStatWidget> HealthBar = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UPlayerStatWidget> StaminaBar = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<AFWCharacter> FWCharacter = nullptr;

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

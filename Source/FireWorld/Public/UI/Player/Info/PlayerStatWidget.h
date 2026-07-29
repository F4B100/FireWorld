// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PlayerStatWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UPlayerStatWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> StatNameBlock = nullptr;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> StatValueBlock = nullptr;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> StatBar = nullptr;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText StatName = FText();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor StatColor = FColor::Black;

	void NativePreConstruct() override;

	void UpdateStatValue(float CurrentVal, float Max);
};

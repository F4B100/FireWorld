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
UCLASS(Blueprintable)
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	FText StatName = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	FLinearColor StatColor = FColor::Black;

	void UpdateStatValue(float CurrentVal, float Max);

protected:
	void NativePreConstruct() override;
};

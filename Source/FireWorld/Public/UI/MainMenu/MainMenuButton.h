// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MainMenuButton.generated.h"

class UImage;
class UOverlay;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UMainMenuButton : public UCommonUserWidget
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<APlayerController> Controller = nullptr;
	UPROPERTY()
	FVector2D CurrentAttractionOffset = FVector2D(0.0f, 0.0f);
	UPROPERTY()
	FVector2D AttractionOffset = FVector2D(0.0f, 0.0f);
	UPROPERTY()
	float AttractionOffsetInterpTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UOverlay> BackgroundOverlay = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UImage> Background = nullptr;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> ButtonMaterial = nullptr;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D AttractionArea = FVector2D(120.0f, 30.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttractionSpeed = 1.0f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWCharacterHUDWidgetBase.h"
#include "FWPlayerInteractionWidget.generated.h"

class UInteractionManager;
class USizeBox;
class AFWController;
class UInteractibleActor;
class UTextBlock;
class IInteractibleActor;
/**
 *
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWPlayerInteractionWidget : public UFWCharacterHUDWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInteractionManager> InteractionManager;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<AActor> CurrentInteractible = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> InteractibleKey;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextBlock> InteractibleText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<USizeBox> ContentSizeBox;
public:
	UFUNCTION(BlueprintCallable)
	void UpdateText() const;
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

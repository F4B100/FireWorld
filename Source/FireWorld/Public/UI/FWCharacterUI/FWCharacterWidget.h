// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWCharacterHUDWidgetBase.h"
#include "FWCharacterWidget.generated.h"

class UFWPlayerInteractionWidget;
class AFWCharacter;
/**
 * 
 */
UCLASS()
class FIREWORLD_API UFWCharacterWidget : public UFWCharacterHUDWidgetBase
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWPlayerInteractionWidget> InteractionWidget = nullptr;
public:

	UFUNCTION(BlueprintCallable)
	UFWPlayerInteractionWidget *GetInteractionWidget() {return InteractionWidget;}
};

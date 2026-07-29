// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FPPlayerUI.generated.h"

class UEnhancedInputComponent;
class UPlayerInventoryView;
class UWidgetSwitcher;
class UFWPlayerInteractionWidget;
class AFWCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFPPlayerUI : public UCommonUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<AFWCharacter> FWCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UFWPlayerInteractionWidget> InteractionWidget = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> InventorySwitcher = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UWidget> InventoryWidget = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UWidget> DefaultWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> OpenMenuAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Input")
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	UFWPlayerInteractionWidget *GetInteractionWidget() {return InteractionWidget;}

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
	UFUNCTION(BlueprintCallable)
	bool IsInInventory();

	UFUNCTION(BlueprintNativeEvent)
	void InventoryFocusSwitched(bool InFocus);

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};


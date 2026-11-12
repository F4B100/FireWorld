// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FPPlayerUI.generated.h"

class UWeapon;
class UWeaponManager;
class AFWPlayerState;
class UItemManagerComponent;
class UInventoryItemView;
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

	bool bIsInInventory = false;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<AFWCharacter> FWCharacter = nullptr;
	UPROPERTY()
	TObjectPtr<UWeaponManager> WeaponManager = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UFWPlayerInteractionWidget> InteractionWidget = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UWidget> InventoryWidget = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UWidget> DefaultWidget = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UInventoryItemView> CurrentWeapon = nullptr;
	
protected:
	UFUNCTION()
	void OnWeaponChangedHandler(UWeapon* Weapon) const;
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;	
	
public:
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ToggleInventoryAnimation = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> OpenMenuAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Input")
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UFUNCTION(BlueprintCallable)
	UFWPlayerInteractionWidget *GetInteractionWidget() {return InteractionWidget;}

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
	UFUNCTION(BlueprintCallable)
	bool IsInInventory();

	UFUNCTION(BlueprintNativeEvent)
	void InventoryFocusSwitched(bool InFocus);
};


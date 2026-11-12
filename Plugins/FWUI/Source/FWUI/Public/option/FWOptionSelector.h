// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "CommonUserWidget.h"
#include "FWMenuEntry.h"
#include "FWOptionSelector.generated.h"

class UCommonBorder;
class UFWMenuEntry;
struct FFWEntryData;
class UFWEntryDataOption;
class UCommonListView;

USTRUCT(BlueprintType)
struct FFWEntryCreateInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UObject> UserData;
};

class UCommonHierarchicalScrollBox;
class USizeBox;
class UImage;
/**
 * 
 */
UCLASS(Blueprintable)
class FWUI_API UFWOptionSelector : public UCommonUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UImage> SelectionViewer = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<USizeBox> SizeBox = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCommonListView> OptionSelector = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCommonBorder> SelectionHover = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCommonBorder> LeftBorder = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCommonBorder> MiddleBorder = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCommonBorder> RightBorder = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstance = nullptr;
	
	
	UPROPERTY()
	float CurrentOffsetTime = 0.0f;
	UPROPERTY()
	float CurrentOffsetStart = 0.0f;
	UPROPERTY()
	float CurrentOffset = 0.0f;
	UPROPERTY()
	int32 InFocusIndex = 0;
	UPROPERTY()
	float CurrentSize = 0.0f;
	UPROPERTY()
	double SelectionAnimationStartTime = 0.0;
	UPROPERTY()
	float SelectionAnimationDuration = 1.0f;
	
	UPROPERTY()
	TObjectPtr<UFWMenuObject> SelectedMenuObject = nullptr;
	
	UFWOptionSelector();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnSelectionChanged,
		const UFWMenuObject *,
		Selection,
		const UFWOptionSelector *,
		Selector
	);
	
	// Event Handlers
	UFUNCTION()
	FEventReply SelectionHoverOnMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	UFUNCTION()
	FEventReply LeftBorderOnMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	UFUNCTION()
	FEventReply RightBorderOnMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	
	// Utilities
	UFUNCTION(BlueprintCallable)
	void CreateAndAddOptionWidget(FString Content, UObject *UserContent, bool AtCustomIndex = false, int32 Index = 0);

public:
	UPROPERTY(Blueprintable, EditDefaultsOnly, Category = "FW")
	TSubclassOf<UFWMenuEntry> EntryClass = nullptr;
	UPROPERTY(BlueprintAssignable, Category = "FW")
	FOnSelectionChanged OnSelectionChanged;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FW")
	float OptionMaxSize = 25.0f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "FW")
	TObjectPtr<UMaterialInterface> MaterialInterface = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "FW")
	TArray<FFWEntryCreateInfo> InitialOptions = TArray<FFWEntryCreateInfo>();
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "FW")
	bool bIsFocusedOptionInteractible = false;
	
	
	UFUNCTION(BlueprintCallable)
	void AddOption(FFWEntryCreateInfo CreateInfo);
	UFUNCTION(BlueprintCallable)
	void AddOptions(TArray<FFWEntryCreateInfo> CreateInfoArr);
	UFUNCTION(BlueprintCallable)
	void SetSelected(FString Name, bool Animate);
	
	UFUNCTION(BlueprintCallable, NotBlueprintable)
	UFWMenuObject* GetSelected();
	
	UFUNCTION()
	void SelectionChanged(UFWMenuObject* SelectionInFocus) const;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

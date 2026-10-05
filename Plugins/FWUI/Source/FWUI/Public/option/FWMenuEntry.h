// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FWMenuEntry.generated.h"

class USizeBox;
class UButton;
class UCommonTextBlock;
/**
 * 
 */


USTRUCT(BlueprintType)
struct FFWEntryData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	int32 Index = -1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Content = TEXT("Default");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UObject> UserData = nullptr;
	UPROPERTY(BlueprintReadOnly)
	bool bIsSpacer = false;
	UPROPERTY(BlueprintReadOnly)
	float SizeEntry = 0.0f;
};

UCLASS(BlueprintType)
class FWUI_API UFWMenuObject : public UObject
{
	GENERATED_BODY()
	FFWEntryData Data = {};
public:
	UFUNCTION(BlueprintCallable)
	FFWEntryData &GetEntryData() {return Data;}
	UFUNCTION(BlueprintCallable)
	void SetEntryData(const FFWEntryData NewData) {Data = NewData;}
	UFUNCTION(BlueprintCallable)
	void SetSize(const float NewSize) {Data.SizeEntry = NewSize;}
};

UCLASS(Blueprintable, BlueprintType)
class FWUI_API UFWMenuEntry : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UCommonTextBlock> TextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> SelectionButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	USizeBox* EntrySizeBox;
	
	UPROPERTY()
	TObjectPtr<UWidget> ListParent = nullptr;
	 
public:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn))
	TObjectPtr<UFWMenuObject> EntryData = nullptr;
	
	UFUNCTION(BlueprintCallable)
	const TSoftObjectPtr<UFWMenuObject> GetDataObject() const;
	UFUNCTION()
	void HandleClicked() const;

	DECLARE_DYNAMIC_DELEGATE_OneParam(
		FOnEntrySelected,
		TSoftObjectPtr<UFWMenuObject>,
		EntryContent
	);
	
	FOnEntrySelected OnEntrySelected;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

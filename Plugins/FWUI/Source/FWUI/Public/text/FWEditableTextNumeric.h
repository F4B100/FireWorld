// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWEditableTextNumeric.generated.h"

class UEditableText;
/**
 * 
 */
UCLASS()
class FWUI_API UFWEditableTextNumeric : public UCommonUserWidget
{
	GENERATED_BODY()
	
	FText LastGoodText = FText();
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UEditableText> EditableText = nullptr;

	UFUNCTION()
	void HandleOnTextChanged(const FText& Text);
	UFUNCTION()
	void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitType);

protected:
	virtual void NativePreConstruct() override;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options|Clamp")
	float MinimumValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options|Clamp")
	float MaximumValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options|Clamp")
	bool bShouldClampValue = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options|Clamp")
	bool bShouldRound = false;
	
	UFUNCTION(BlueprintCallable)
	void SetTextValue(float Value);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChanged, float, Value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueCommitted, float, Value, ETextCommit::Type, CommitMethod);

	UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnValueChanged (Numeric Editable Text)"))
	FOnValueChanged OnValueChanged;
	UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnValueCommitted (Numeric Editable Text)"))
	FOnValueCommitted OnValueCommitted;
};

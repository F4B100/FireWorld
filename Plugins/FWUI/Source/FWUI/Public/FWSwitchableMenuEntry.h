// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FWSwitchableMenuEntry.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class FWUI_API UFWSwitchableMenuEntry : public UCommonUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = FWUI, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButton> ExitButton = nullptr;
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitClicked);
	
	UPROPERTY(BlueprintAssignable)
	FOnExitClicked OnExitClicked;
	
	UFUNCTION()
	void OnExitButtonClicked();
protected:
	virtual void NativeConstruct() override;
};

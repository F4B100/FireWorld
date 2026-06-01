// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FWGlobalGI.generated.h"

class UFWSaveGame;
/**
 * 
 */
UCLASS(Blueprintable)
class FIREWORLD_API UFWGlobalGI : public UGameInstance
{
public:
	UPROPERTY(BlueprintReadWrite, Category=Save)
	TObjectPtr<UFWSaveGame> FWSaveGame = nullptr;
	UPROPERTY(BlueprintReadOnly, Category=Save)
	FString Name = "FWSaveGI";
	
	UFWGlobalGI();
	
	virtual void StartGameInstance() override;

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	bool CreateSaveGame();
	UFUNCTION(BlueprintCallable)
	bool DoesSaveExist();
private:
	GENERATED_BODY()
};

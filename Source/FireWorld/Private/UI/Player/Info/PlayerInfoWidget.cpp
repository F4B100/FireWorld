// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/Info/PlayerInfoWidget.h"

#include "Character/FWCharacter.h"
#include "Gameplay/Component/PlayerStatsComponent.h"
#include "UI/Player/Info/PlayerStatWidget.h"

void UPlayerInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FWCharacter = GetOwningPlayerPawn<AFWCharacter>();
}

void UPlayerInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (FWCharacter)
	{
		TObjectPtr<UPlayerStatsComponent> PlayerStats = FWCharacter.Get()->GetPlayerStats();
		if (PlayerStats)
		{
			HealthBar.Get()->UpdateStatValue(PlayerStats.Get()->GetHealth(), PlayerStats.Get()->GetMaxHealth());
			HealthBar.Get()->UpdateStatValue(PlayerStats.Get()->GetStamina(), PlayerStats.Get()->GetMaxStamina());
		}
	}
}

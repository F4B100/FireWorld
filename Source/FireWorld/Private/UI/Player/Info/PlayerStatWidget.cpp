// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/Info/PlayerStatWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerStatWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	StatNameBlock.Get()->SetText(StatName);
	StatValueBlock.Get()->SetText(FText::FromString("0.0"));
	StatBar.Get()->SetFillColorAndOpacity(StatColor);
}

void UPlayerStatWidget::UpdateStatValue(float CurrentVal, float Max)
{
	StatBar->SetPercent(CurrentVal / Max);
	StatValueBlock.Get()->SetText(FText::FromString(FString::Printf(TEXT("%f"), CurrentVal)));
}

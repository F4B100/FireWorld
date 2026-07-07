// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FWCharacterUI/FWPlayerInteractionWidget.h"

#include "Character/FWCharacter.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Gameplay/Interactible/InteractibleActor.h"
#include "Gameplay/Component/InteractionManager.h"

void UFWPlayerInteractionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateText();
	if (FWCharacter)
	{
		InteractionManager = FWCharacter.Get()->GetInteractionManager();
	}
}

void UFWPlayerInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!InteractionManager)
	{
		return;
	}
	AActor *Interactable = InteractionManager.Get()->GetCurrentInteractible();
	if (CurrentInteractible != Interactable)
	{
		CurrentInteractible = Interactable;
		UpdateText();
	}
}

void UFWPlayerInteractionWidget::UpdateText() const
{
	if (CurrentInteractible)
	{
		IInteractibleActor *InteractibleActor = Cast<IInteractibleActor>(CurrentInteractible);
		InteractibleKey->SetText(FText::FromString(TEXT("E")));
		InteractibleText->SetText(InteractibleActor->GetInteractibleActorName());
		ContentSizeBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InteractibleKey->SetText(FText::FromString(TEXT(" ")));
		InteractibleText->SetText(FText::FromString(TEXT(" ")));
		ContentSizeBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuButton.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Engine/Engine.h"
#include "Framework/Application/SlateApplication.h"
#include "Materials/MaterialInstanceDynamic.h"

void UMainMenuButton::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = GetOwningPlayer();
	ButtonMaterial = Background.Get()->GetDynamicMaterial();
}

void UMainMenuButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Controller)
	{
		const FVector2D LocalMouse = MyGeometry.AbsoluteToLocal(FSlateApplication::Get().GetCursorPos());
		const FVector2D LocalCenter = MyGeometry.GetLocalSize() * 0.5f;
		const FVector2D Delta = LocalMouse - LocalCenter;

		if (FMath::Abs(Delta.X) <= AttractionArea.X && FMath::Abs(Delta.Y) <= AttractionArea.Y){
			AttractionOffset = Delta;
		}
		else
		{
			AttractionOffset = FVector2D::Zero();
		}
		CurrentAttractionOffset += (AttractionOffset - CurrentAttractionOffset) * InDeltaTime * AttractionSpeed;
		BackgroundOverlay.Get()->SetRenderTranslation(CurrentAttractionOffset);
		FVector2D MaterialUVOffset;
		{
			FVector2D Temp = LocalMouse - (LocalCenter + CurrentAttractionOffset);
			MaterialUVOffset = FVector2D(Temp.X / MyGeometry.GetLocalSize().X, Temp.Y / MyGeometry.GetLocalSize().Y);
		}
		if (ButtonMaterial)
		{
			ButtonMaterial.Get()->SetScalarParameterValue("OffsetX", MaterialUVOffset.X + 0.5f);
			ButtonMaterial.Get()->SetScalarParameterValue("OffsetY", MaterialUVOffset.Y + 0.5f);
		}

	}
}

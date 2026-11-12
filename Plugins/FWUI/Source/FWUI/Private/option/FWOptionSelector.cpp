// Fill out your copyright notice in the Description page of Project Settings.


#include "option/FWOptionSelector.h"

#include "CommonBorder.h"
#include "CommonListView.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBoxSlot.h"
#include "option/FWMenuEntry.h"

UFWOptionSelector::UFWOptionSelector()
{
}


FEventReply UFWOptionSelector::SelectionHoverOnMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	FVector2f Pos = MyGeometry.AbsoluteToLocal(FSlateApplication::Get().GetCursorPos());
	float Selected = FMath::RoundToZero(Pos.X / OptionMaxSize);
	int32 NumItems = OptionSelector->GetNumItems();
	if (Selected < NumItems && Selected >= 0.0f)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(31232141, 10.0f, FColor::Emerald, FString::Printf(TEXT("%f\n"), Selected));
		}
		
		CurrentOffsetStart = CurrentOffset;
		CurrentOffsetTime = 0.0f;
		SelectionAnimationStartTime = FPlatformTime::Seconds();
		InFocusIndex = Selected;
	}
	
	SelectedMenuObject = Cast<UFWMenuObject>(OptionSelector->GetItemAt(InFocusIndex + 1));
	SelectionChanged(SelectedMenuObject);
	
	return FEventReply(true);
}

FEventReply UFWOptionSelector::LeftBorderOnMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	CurrentOffsetStart = CurrentOffset;
	CurrentOffsetTime = 0.0f;
	SelectionAnimationStartTime = FPlatformTime::Seconds();
	InFocusIndex = FMath::Clamp(InFocusIndex - 1, 0, OptionSelector->GetNumItems() - 3);
	
	SelectedMenuObject = Cast<UFWMenuObject>(OptionSelector->GetItemAt(InFocusIndex + 1));
	
	SelectionChanged(SelectedMenuObject);
	return FEventReply(true);	
}


FEventReply UFWOptionSelector::RightBorderOnMouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	CurrentOffsetStart = CurrentOffset;
	CurrentOffsetTime = 0.0f;
	SelectionAnimationStartTime = FPlatformTime::Seconds();
	InFocusIndex = FMath::Clamp(InFocusIndex + 1, 0, OptionSelector->GetNumItems() - 3);
	
	SelectedMenuObject = Cast<UFWMenuObject>(OptionSelector->GetItemAt(InFocusIndex + 1));
	
	SelectionChanged(SelectedMenuObject);
	return FEventReply(true);
}

void UFWOptionSelector::CreateAndAddOptionWidget(FString Content, UObject *UserContent, bool AtCustomIndex, int32 Index)
{
	if (Content.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to Add am empty Entry to UFWOptionSelector: %s"), *this->GetName())
		return;
	}
	const int32 NumItems = OptionSelector->GetNumItems();
	UFWMenuObject *EntryData = nullptr;
	if (AtCustomIndex)
	{
		if (Index >= NumItems || Index < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Custom index out of bounds when trying to add Entry to UFWOptionSelector: %s"), *this->GetName())
			return;
		}
		EntryData = NewObject<UFWMenuObject>(this, UFWMenuObject::StaticClass());
		EntryData->SetEntryData({.Index = Index, .Content = FString(), .UserData = nullptr, .bIsSpacer = false});
		OptionSelector->AddItemAt(EntryData, Index);
	} else {
		EntryData = NewObject<UFWMenuObject>(this, UFWMenuObject::StaticClass());
		EntryData->SetEntryData({.Index = NumItems - 1, .Content = Content, .UserData = UserContent, .bIsSpacer = false});
		OptionSelector->AddItemAt(EntryData, NumItems - 1);
	}

	if (!SelectedMenuObject && EntryData)
	{
		SelectedMenuObject = EntryData;
	}
	
	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsX"), OptionSelector->GetNumItems() - 2);
	}
	if (SizeBox)
	{
		SizeBox.Get()->SetWidthOverride(OptionMaxSize * OptionSelector->GetNumItems() - 2);
		SizeBox.Get()->SetHeightOverride(OptionMaxSize);
	}
}


void UFWOptionSelector::AddOption(FFWEntryCreateInfo CreateInfo)
{
	CreateAndAddOptionWidget(CreateInfo.Name, CreateInfo.UserData);
	UE_LOG(LogTemp, Error, TEXT("Num Opts:%d\n"), OptionSelector->GetNumItems())
	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsX"), OptionSelector->GetNumItems() - 2);
	}
	if (SizeBox)
	{
		SizeBox.Get()->SetWidthOverride(OptionMaxSize * (OptionSelector->GetNumItems() - 2));
	}
}

void UFWOptionSelector::AddOptions(TArray<FFWEntryCreateInfo> CreateInfoArr)
{
	for (auto [Name, UserData] : CreateInfoArr)
	{
		CreateAndAddOptionWidget(Name, UserData);
	}
	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsX"), OptionSelector->GetNumItems() - 2);
	}
	if (SizeBox)
	{
		SizeBox.Get()->SetWidthOverride(OptionMaxSize * (OptionSelector->GetNumItems() - 2));
	}
}

void UFWOptionSelector::SetSelected(FString Name, bool Animate)
{
	if (Name.IsEmpty())
	{
		return;
	}
	int i = 0;
	for (auto Element : OptionSelector->GetListItems())
	{
		UFWMenuObject *Data = Cast<UFWMenuObject>(Element);
		if (Data->GetEntryData().Content.Equals(Name))
		{
			InFocusIndex = i - 1;
			SelectedMenuObject = Data;
			if (!Animate)
			{
				CurrentOffset = InFocusIndex;
				
				if (MaterialInstance)
				{
					MaterialInstance->SetScalarParameterValue(TEXT("InFocusX"), CurrentOffset);
				}
				OptionSelector->SetScrollOffset(CurrentOffset);
			}
		}
		i++;
	}
}

UFWMenuObject* UFWOptionSelector::GetSelected()
{
	return SelectedMenuObject;
}

void UFWOptionSelector::SelectionChanged(UFWMenuObject* SelectionInFocus) const
{
	OnSelectionChanged.Broadcast(SelectionInFocus, this);
}

void UFWOptionSelector::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (IsDesignTime()){
		if (SelectionViewer && !MaterialInstance)
		{
			if (MaterialInterface)
			{
				SelectionViewer.Get()->SetBrushFromMaterial(MaterialInterface);
			}
		
			MaterialInstance = SelectionViewer->GetDynamicMaterial();
		}
	
	
		if (MaterialInstance)
		{
			MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsX"), OptionSelector->GetNumItems() - 2);
			MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsY"), 1.0);
		}
		
		if (SizeBox)
		{
			SizeBox->SetHeightOverride(OptionMaxSize);
			SizeBox->SetWidthOverride(OptionMaxSize * (OptionSelector->GetNumItems() - 2));
		}
		if (UWorld* World = GetWorld())
		{
			if (UUserWidget* RootWidget = Cast<UUserWidget>(GetTypedOuter<UUserWidget>()))
			{
				RootWidget->ForceLayoutPrepass();
			}
		}

		const FVector2D DesiredSize = GetDesiredSize();
		for (auto Element : OptionSelector->GetListItems())
		{
			TObjectPtr<UFWMenuObject> MenuObject = Cast<UFWMenuObject>(Element);
			if (MenuObject)
			{
				MenuObject->SetSize(CurrentSize / 3.0f);
			}
		}
	}
}

void UFWOptionSelector::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Addint the two spacers
	UFWMenuObject *EntryData = NewObject<UFWMenuObject>(this, UFWMenuObject::StaticClass());
	EntryData->SetEntryData({.Index = 0, .Content = FString(), .UserData = nullptr, .bIsSpacer = true});
	OptionSelector->AddItem(EntryData);
	
	EntryData = NewObject<UFWMenuObject>(this, UFWMenuObject::StaticClass());
	EntryData->SetEntryData({.Index = 0, .Content = FString(), .UserData = nullptr, .bIsSpacer = true});
	OptionSelector->AddItem(EntryData);
	
	for (auto Element : InitialOptions)
	{
		CreateAndAddOptionWidget(Element.Name, Element.UserData);
	}
	
	if (SizeBox)
	{
		SizeBox->SetHeightOverride(OptionMaxSize);
		if (SizeBox)
		{
			SizeBox->SetHeightOverride(OptionMaxSize);
			SizeBox->SetWidthOverride(OptionMaxSize * (OptionSelector->GetNumItems() - 2));
		}
	}
	
	if (SelectionViewer && !MaterialInstance)
	{
		if (MaterialInterface)
		{
			SelectionViewer.Get()->SetBrushFromMaterial(MaterialInterface);
		}
		
		MaterialInstance = SelectionViewer->GetDynamicMaterial();
	}
	
	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsX"), OptionSelector->GetNumItems() - 2);
		MaterialInstance->SetScalarParameterValue(TEXT("NumberOfOptionsY"), 1.0);
	}

	if (SelectionHover)
	{
		SelectionHover.Get()->OnMouseButtonDownEvent.BindDynamic(this, &UFWOptionSelector::SelectionHoverOnMouseDown);
	}

	if (LeftBorder)
	{
		LeftBorder->OnMouseButtonDownEvent.BindDynamic(this, &UFWOptionSelector::LeftBorderOnMouseDown);
	}

	if (MiddleBorder)
	{
		if (bIsFocusedOptionInteractible)
		{
			MiddleBorder.Get()->SetVisibility(ESlateVisibility::Hidden);	
		}
	}
	
	if (RightBorder)
	{
		RightBorder->OnMouseButtonDownEvent.BindDynamic(this, &UFWOptionSelector::RightBorderOnMouseDown);
	}
	if (UWorld* World = GetWorld())
	{
		if (UUserWidget* RootWidget = Cast<UUserWidget>(GetTypedOuter<UUserWidget>()))
		{
			RootWidget->ForceLayoutPrepass();
		}
	}

	const FVector2D DesiredSize = GetDesiredSize();
	for (auto Element : OptionSelector->GetListItems())
	{
		TObjectPtr<UFWMenuObject> MenuObject = Cast<UFWMenuObject>(Element);
		if (MenuObject)
		{
			MenuObject->SetSize(CurrentSize / 3.0f);
		}
	}
}


void UFWOptionSelector::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentSize != MyGeometry.GetLocalSize().X)
	{
		CurrentSize = MyGeometry.GetLocalSize().X;
		for (auto Element : OptionSelector->GetListItems())
		{
			TObjectPtr<UFWMenuObject> MenuObject = Cast<UFWMenuObject>(Element);
			if (MenuObject)
			{
				MenuObject->SetSize(CurrentSize / 3.0f);
			}
		}
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(412414, 10.0f, FColor::Purple, FString::Printf(TEXT("%f\n"), SizeBox->GetWidthOverride()));
	}
	
	const double ElapsedTime = FPlatformTime::Seconds() - SelectionAnimationStartTime;
	CurrentOffsetTime = FMath::Clamp(
		static_cast<float>(ElapsedTime / SelectionAnimationDuration),
		0.0f,
		1.0f);
	if (InFocusIndex - CurrentOffsetStart != 0.0f && CurrentOffsetTime < 1.0f)
	{
		CurrentOffset = FMath::InterpExpoOut(
			CurrentOffsetStart,
			static_cast<float>(InFocusIndex),
			CurrentOffsetTime);
	}
	else
	{
		CurrentOffset = InFocusIndex;
		CurrentOffsetStart = InFocusIndex;
	}

	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue(TEXT("InFocusX"), CurrentOffset);
	}
	OptionSelector->SetScrollOffset(CurrentOffset);
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "text/FWEditableTextNumeric.h"

// Fill out your copyright notice in the Description page of Project Settings.	

#include "Blueprint/WidgetTree.h"
#include "Components/EditableText.h"
#include "Misc/DefaultValueHelper.h"

void UFWEditableTextNumeric::HandleOnTextChanged(const FText& Text)
{
	if (Text.IsNumeric() || Text.IsEmpty())
	{
		EditableText->SetText(Text);
		LastGoodText = Text;
	}
	else
	{
		EditableText->SetText(LastGoodText);
	}
}

void UFWEditableTextNumeric::HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitType) const
{
	
	float Value = 0.0f;
	FDefaultValueHelper::ParseFloat(Text.ToString(), Value);
	OnValueCommitted.Broadcast(Value, CommitType);
	if (bShouldClampValue)
	{
		Value = FMath::Clamp(Value, MinimumValue, MaximumValue);
	}
	
	OnValueCommitted.Broadcast(Value, CommitType);
}

void UFWEditableTextNumeric::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (EditableText)
	{
		EditableText->OnTextChanged.AddUniqueDynamic(this, &UFWEditableTextNumeric::HandleOnTextChanged);

		EditableText->OnTextCommitted.AddUniqueDynamic(this, &UFWEditableTextNumeric::HandleOnTextCommitted);
	}
}

void UFWEditableTextNumeric::SetTextValue(float Value)
{
	if (bShouldClampValue)
	{
		FFormatOrderedArguments  Args;
		Args.Add(FFormatArgumentValue(FMath::Clamp(Value, MinimumValue, MaximumValue)));
		EditableText->SetText(FText::Format(FText::FromString(TEXT("{0}")),Args));
	}
	else
	{
		FFormatOrderedArguments  Args;
		Args.Add(FFormatArgumentValue(Value));
		EditableText->SetText(FText::Format(FText::FromString(TEXT("{0}")),Args));
	}
}

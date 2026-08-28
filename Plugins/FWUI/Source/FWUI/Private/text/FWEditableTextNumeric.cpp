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
		if (bShouldClampValue)
		{
			float Value = 0.0f;
			if (!Text.IsEmpty())
			{
				FDefaultValueHelper::ParseFloat(Text.ToString(), Value);
			}
			Value = FMath::Clamp(Value, MinimumValue, MaximumValue);
			FFormatOrderedArguments  Args;
			Args.Add(FFormatArgumentValue(Value));
			FText NewText = FText::Format(FText::FromString(TEXT("{0}")),Args);
			EditableText->SetText(NewText);
			LastGoodText = NewText;
			OnValueChanged.Broadcast(Value);
		}
		else
		{
			EditableText->SetText(Text);
			LastGoodText = Text;
			
			float Value = 0.0f;
			FDefaultValueHelper::ParseFloat(Text.ToString(), Value);
			OnValueChanged.Broadcast(Value);
		}
	}
	else
	{
		EditableText->SetText(LastGoodText);
	}
}

void UFWEditableTextNumeric::HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	if (Text.IsNumeric())
	{
		float Value = 0.0f;
		FDefaultValueHelper::ParseFloat(Text.ToString(), Value);
		OnValueCommitted.Broadcast(Value, CommitType);
	}
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

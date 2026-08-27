// Fill out your copyright notice in the Description page of Project Settings.


#include "FWUIBlueprintLibrary.h"

#include "Misc/DefaultValueHelper.h"

float UFWUIBlueprintLibrary::StringToFloat(FString String)
{
	float Val = 0.0;
	FDefaultValueHelper::ParseFloat(String, Val);
	return Val;
}

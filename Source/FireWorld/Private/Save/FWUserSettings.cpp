// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/FWUserSettings.h"

UFWUserSettings* UFWUserSettings::GetFWGameUserSettings()
{
	return Cast<UFWUserSettings>(GetGameUserSettings());
}

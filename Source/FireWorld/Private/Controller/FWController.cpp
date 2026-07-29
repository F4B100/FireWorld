// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FWController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FWGameInstance.h"
#include "Character/FWCharacter.h"
#include "Engine/Engine.h"
#include "HUD/FWCharacterHUD.h"
#include "Save/FWSaveGame.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "UserSettings/EnhancedInputUserSettings.h"

AFWController::AFWController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFWController::BeginPlay()
{
	FWGameInstance = Cast<UFWGameInstance>(GetGameInstance());
	Super::BeginPlay();
	const FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	FWHUD = Cast<AFWCharacterHUD>(GetHUD());
}

void AFWController::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);
	
	FWCharacter = Cast<AFWCharacter>(APawn);
}

void AFWController::StartShooting(const FInputActionValue& InputActionValue)
{
	if (FWCharacter)
	{
		FWCharacter->Fire();
	}
}

void AFWController::StopShooting(const FInputActionValue& InputActionValue)
{
	if (FWCharacter)
	{
		FWCharacter->StopFire();
	}
}


void AFWController::SprintDown()
{
	if (FWCharacter)
	{
		FWCharacter->SprintPressed();
	}
}

void AFWController::SprintUp()
{
	if (FWCharacter)
	{
		FWCharacter->SprintReleased();
	}
}

void AFWController::HandleCrouch(const FInputActionValue& InputActionValue)
{
	if (!FWCharacter)
	{
		return;
	}
	const float CrouchPress = InputActionValue.Get<float>();
	if (!FWCharacter->bIsCrouched && CrouchPress > 0.5f)
	{
		FWCharacter->Crouch();
	}
	if (FWCharacter->bIsCrouched && CrouchPress < 0.5f)
	{
		FWCharacter->UnCrouch();
	}
}

void AFWController::OnJump()
{
	if (FWCharacter)
	{
		FWCharacter->Jump();
	}
}

void AFWController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovVector = InputActionValue.Get<FVector2D>().GetSafeNormal();
	if (FWCharacter)
	{
		FWCharacter->AddMovementInput(MovVector);
	}
}

void AFWController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	
	if (FWCharacter)
	{
		FWCharacter->AddLookInput(LookVector);
	}
}

void AFWController::HandleMenuOpen(const FInputActionValue& InputActionValue)
{
	if (FWHUD)
	{
		FWHUD.Get()->MainWidget.Get()->ToggleInventory();
		if (FWHUD.Get()->MainWidget.Get()->IsInInventory())
		{
			const FInputModeUIOnly Input = FInputModeUIOnly();
			SetShowMouseCursor(true);
			SetInputMode(Input);
			FWHUD.Get()->MainWidget->SetFocus();
		} else
		{
			const FInputModeGameOnly Input = FInputModeGameOnly();
			SetShowMouseCursor(false);
			SetInputMode(Input);
		}
	}
}

void AFWController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FWGameInstance.Get()->CurrentLoadedSave)
	{
		UFWSaveGame *SaveGame = FWGameInstance.Get()->CurrentLoadedSave;

		SaveGame->PlayerData.Empty();
		FMemoryWriter PlayerWriter = FMemoryWriter(SaveGame->PlayerData);
		FObjectAndNameAsStringProxyArchive Ar(PlayerWriter, true);
		Ar.ArIsSaveGame = true;
		FWCharacter->Serialize(Ar);
	}

	if (FWGameInstance && FWGameInstance.Get()->GetShouldSaveGame())
	{
		FWGameInstance->SaveGame();
	}
}

void AFWController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	
	FWCharacter = Cast<AFWCharacter>(P);
}

void AFWController::Interact(const FInputActionValue& InputActionValue)
{
	if (FWCharacter)
	{
		FWCharacter.Get()->Interact();
	}
}

void AFWController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		if (InputSubsystem != nullptr)
		{
			UEnhancedInputUserSettings* UserSettings = InputSubsystem->GetUserSettings();
			if (
				UserSettings &&
				!UserSettings->IsMappingContextRegistered(InputMappingComponent)
			) {
				UserSettings->RegisterInputMappingContext(InputMappingComponent);
			}
		}

		if (InputSubsystem && InputMappingComponent)
		{
			InputSubsystem->ClearAllMappings();
			InputSubsystem->AddMappingContext(InputMappingComponent, 0);
		}
	}

	if (EnhancedInputComponent)
	{
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFWController::OnJump);
		}

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFWController::SprintDown);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFWController::SprintUp);
		}
		
		if (CrouchAction)
		{
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AFWController::HandleCrouch);
			}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFWController::HandleMove);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFWController::HandleLook);
		}

		if (ShootAction)
		{
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AFWController::StartShooting);
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AFWController::StopShooting);
		}

		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFWController::Interact);
		}

		if (OpenMenuAction)
		{
			EnhancedInputComponent->BindAction(OpenMenuAction, ETriggerEvent::Started, this, &AFWController::HandleMenuOpen);
		}
	}
}

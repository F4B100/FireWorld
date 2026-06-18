// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FWControllerFP.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/FWCharacterFP.h"
#include "UserSettings/EnhancedInputUserSettings.h"


// Sets default values
AFWControllerFP::AFWControllerFP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFWControllerFP::BeginPlay()
{
	Super::BeginPlay();
}

void AFWControllerFP::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);
	
	FWCharacter = Cast<AFWCharacterFP>(APawn);
}

void AFWControllerFP::SprintDown()
{
	if (FWCharacter)
	{
		FWCharacter->SprintPressed();
	}
}

void AFWControllerFP::SprintUp()
{
	if (FWCharacter)
	{
		FWCharacter->SprintReleased();
	}
}

void AFWControllerFP::HandleCrouch(const FInputActionValue& InputActionValue)
{
	const float CrouchPress = InputActionValue.Get<float>();
	if (!FWCharacter)
	{
		return;
	}
	if (!FWCharacter->bIsCrouched && CrouchPress > 0.5f)
	{
		FWCharacter->Crouch();
	}
	if (FWCharacter->bIsCrouched && CrouchPress < 0.5f)
	{
		FWCharacter->UnCrouch();
	}
}

void AFWControllerFP::OnJump()
{
	if (FWCharacter)
	{
		FWCharacter->Jump();
	}
}

void AFWControllerFP::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovVector = InputActionValue.Get<FVector2D>().GetSafeNormal();
	if (FWCharacter)
	{
		FWCharacter->AddMovementInput(MovVector);
	}
}

void AFWControllerFP::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	
	if (FWCharacter)
	{
		FWCharacter->AddLookInput(LookVector);
	}
}

void AFWControllerFP::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFWControllerFP::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	
	FWCharacter = Cast<AFWCharacterFP>(P);
}

void AFWControllerFP::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Input component"));	

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		if (InputSubsystem != nullptr)
		{
			if (
				UEnhancedInputUserSettings* UserSettings = InputSubsystem->GetUserSettings();
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
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFWControllerFP::OnJump);
		}

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFWControllerFP::SprintDown);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFWControllerFP::SprintUp);
		}
		
		if (CrouchAction)
		{
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AFWControllerFP::HandleCrouch);
			}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFWControllerFP::HandleMove);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFWControllerFP::HandleLook);
		}
	}
}

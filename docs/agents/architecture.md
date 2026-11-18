# Architecture and content map

## Unreal project layout

- `FireWorld.uproject`: project descriptor; the project is associated with Unreal Engine 5.8 and enables `FWUI`.
- `Source/FireWorld/Public` and `Source/FireWorld/Private`: public headers and implementations for the `FireWorld` module.
- `Content/Blueprints/Character`, `Controller`, `Gamemode`, and `HUD`: Blueprint-side game framework classes, including `BP_FWCharacterFP`, `BP_FWControllerFP`, `BP_FWGamemodeFP`, and their menu counterparts.
- `Content/Blueprints/Gameplay` and `Content/Blueprints/Interactible`: gameplay assets, weapons, pickups, and level-transition Blueprint.
- `Content/Blueprints/Inputs`: Enhanced Input actions and mapping context. `FPInputMap` is also registered as the default mapping context in `Config/DefaultEngine.ini`.
- `Content/Blueprints/UI`: main menu, settings, inventory, and player HUD widgets.
- `Content/Maps`: includes `MainMenu` and `MainLevel/MainLevel`. The default startup map and editor startup map are configured as `MainMenu`.
- `Plugins/FWUI` and `Plugins/QMovement`: local plugin modules; see [Unreal workflow and plugins](unreal-workflow.md).

## C++ organization

`Source/FireWorld/Public` and `Private` follow matching subsystem directories:

- `Character/`: player character, player state, movement component, and camera manager.
- `Controller/`: player controller and Enhanced Input bindings.
- `Gameplay/Actor`, `Component`, `Interactible`, and `Items`: gameplay actors, reusable components, interactables, inventory items, and weapons.
- `Save/`: save-game data, save-name registry, and user settings.
- `HUD/` and `UI/`: HUD and widgets for player status, inventory, settings, and save selection.

The configured `UFWGameInstance` is `/Script/FireWorld.FWGameInstance`. It owns the active save references and save-name registry. `AFWCharacter` creates the custom `UFWCharacterMovementComponent` and gameplay components; the `AFWPlayerState` owns the `UItemManagerComponent`.

## Change impact

Many gameplay-facing C++ classes are exposed to Blueprint with `UCLASS`, `UPROPERTY`, and `UFUNCTION`. When changing a reflected property, class, input action, widget binding, or asset reference, inspect both the C++ declaration/implementation and the Blueprint/configuration that consumes it. Unreal asset files are binary; do not treat `.uasset` or `.umap` as text sources.

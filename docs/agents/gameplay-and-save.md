# Gameplay, input, and persistence

## Character and controller flow

- `AFWController` binds the Enhanced Input actions assigned to its reflected properties (`JumpAction`, `MoveAction`, `LookAction`, `SprintAction`, `CrouchAction`, `ShootAction`, `InteractAction`, and `OpenMenuAction`). The Blueprint controller supplies these asset references and the mapping context.
- Movement and look input are forwarded to `AFWCharacter`; fire and interaction are forwarded to its components. Opening the menu toggles the HUD inventory and switches between game-only and UI-only input modes.
- `AFWCharacter` constructs `UFWCharacterMovementComponent`, stats, stable-position, key inventory, weapon, and interaction components. The inventory manager is obtained from the `AFWPlayerState`.
- Interactable actors use the `UInteractableActor` interface. The character asks its interaction manager for the current target and invokes the interface on interaction.
- The project character movement system is `UFWCharacterMovementComponent` in `Source/FireWorld/Character`. Do not assume it uses the separate `QMovement` plugin's `AQuakePawn`; see [Unreal workflow and plugins](unreal-workflow.md).

## Inventory and weapons

- `AFWPlayerState` creates `UItemManagerComponent` and loads the active save's `SavedInventory` during `BeginPlay`.
- Inventory entries are `UFWItem` objects. `FSavedItem` stores the item subclass plus serialized bytes; `UItemManagerComponent::SaveInventory` and `LoadInventory` manage conversion to/from `FSavedInventory`.
- `UWeaponManager` observes inventory item-added/removed/moved delegates, equips a `UWeapon`, and stores the equipped inventory index in `FWeaponManagerSavedData`. Weapon firing is delegated to the current weapon.
- When changing inventory or weapon behavior, follow the manager's delegate flow and preserve the custom item serialization path; the inventory is not simply a reflected array of save-game items.

## Save system

- `UFWGameInstance` is configured in `Config/DefaultEngine.ini`. The save-name registry uses slot `SaveNames`; individual save games use the selected save name, with user index `0`.
- `UFWSaveGame` stores player serialized bytes, `FSavedInventory`, weapon-manager data, actor-data maps, and difficulty. `UFWGameInstance` owns `CurrentLoadedSave`, `LoadedSaveName`, and save/load/create/delete operations.
- `AFWCharacter::SaveCharacterData` serializes the character using `FObjectAndNameAsStringProxyArchive` with `ArIsSaveGame` enabled, saves inventory and weapon state, and asks the game instance to write the save. The character also calls this from `EndPlay`.
- `AFWController` has a repeating save timer and gates character data saves on `bShouldSaveGame`. Check both the controller and game instance when changing save timing or triggers.
- `UFWUserSettings` is a separate `UGameUserSettings` subclass; do not conflate user settings with per-save player progress.

## Input and UI

The default Enhanced Input mapping context is `/Game/Blueprints/Inputs/FPInputMap`, registered in `Config/DefaultEngine.ini`. The controller also registers it with Enhanced Input user settings and binds each action in `SetupInputComponent`. When modifying bindings, check the controller's reflected action properties, the Blueprint-assigned assets, and the mapping context together.

The player controller gets `AFWCharacterHUD`, which references the player UI. The menu/inventory action toggles inventory display and input mode. Reusable CommonUI widgets live in `Plugins/FWUI`; game-specific widgets are under `Source/FireWorld/UI` and `Content/Blueprints/UI`.

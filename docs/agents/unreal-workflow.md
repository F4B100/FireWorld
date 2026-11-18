# Unreal workflow and plugins

## Project and build configuration

- `FireWorld.uproject` specifies Unreal Engine 5.8. The game and editor targets under `Source/` use BuildSettings V7 and Unreal 5.8 include order.
- The project has `FireWorld.slnx` and `Automation_FireWorld.slnx`; no `.github` workflows or C++ automation tests were found during the repository survey.
- `Source/FireWorld/FireWorld.Build.cs` declares the main module dependencies, including Enhanced Input, UMG, CommonUI, and FWUI. Plugin module dependencies are defined in each plugin's `*.Build.cs`.
- Default maps, game instance, and game mode are configured in `Config/DefaultEngine.ini`. Default Enhanced Input settings and the project mapping context are also in that file.
- Use the Unreal Editor/build tool associated with the project when validating C++ or Blueprint changes. The presence of generated binaries in the checkout is not proof that the current source change builds.

## Local plugins

### FWUI

`Plugins/FWUI` is an enabled runtime plugin (`FWUI.uplugin`) for reusable UI classes, and its module depends on CommonUI and UMG. Its public API includes menu/list widgets, option selector and editable numeric text widgets, switchable menu entries, and a Blueprint function library. Project-specific UI remains in `Source/FireWorld/UI` and `Content/Blueprints/UI`.

### QMovement

`Plugins/QMovement` contains a separate runtime module implementing `AQuakePawn` and data-driven `UMovementSettings`, with Enhanced Input as a plugin dependency. The plugin directory exists in this repository, but `FireWorld.uproject` does not list QMovement as an enabled project plugin. The project's `AFWCharacter` instead installs its own `UFWCharacterMovementComponent`. Check the descriptor and actual class usage before wiring this plugin into game character behavior.

## Asset and generated-file care

- Unreal assets (`.uasset`, `.umap`) are binary; modify them through Unreal Editor or Unreal-aware tooling and preserve required references.
- Avoid hand-editing `Intermediate/`, `Binaries/`, `Saved/`, and `DerivedDataCache/`; these are generated output or local editor data and are ignored by `.gitignore`.
- Config under `Config/` and source under `Source/` are hand-authored project inputs. Check the matching Blueprint/config values when changing reflected defaults or asset references.

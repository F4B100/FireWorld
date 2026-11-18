# Agent guide

## Project at a glance

FireWorld is an Unreal Engine 5.8 project. The main game module is C++ under `Source/FireWorld`, while gameplay classes, UI, input assets, and game modes are also configured in Blueprint under `Content/Blueprints`. The startup and default game map is `/Game/Maps/MainMenu`; the configured game mode is `/Game/Blueprints/Gamemode/BP_FWGamemodeFP`.

Read the relevant guide before making subsystem changes:

- [Architecture and content map](docs/agents/architecture.md)
- [Gameplay, input, and persistence](docs/agents/gameplay-and-save.md)
- [Unreal workflow and plugins](docs/agents/unreal-workflow.md)

## Working in this repository

- Treat `.h`/`.cpp` in `Source/` and plugin source as hand-authored code; Unreal assets such as `.uasset` and `.umap` are binary and should be changed through Unreal Editor or appropriate Unreal tools.
- Keep C++ changes aligned with the existing module and `Public`/`Private` layout. Check related Blueprint assets and config when changing reflected classes, input, maps, or UI.
- Avoid editing generated or local output under `Intermediate/`, `Binaries/`, `Saved/`, or `DerivedDataCache/`.
- No C++ automation tests or repository CI workflows were found in the initial survey. Use an Unreal build or editor validation for code/asset changes when the engine toolchain is available, and state clearly when it is not.
- Preserve unrelated worktree changes. Review `git status` before editing and inspect the final diff.

## Session knowledge handoff

When you read the exact phrase `goal completed` in a user message, record useful, verified, reusable information learned during that session in the most relevant guide under `docs/agents/`. If it applies to the whole project, update this file instead. Integrate or correct existing guidance rather than duplicating it; do not record secrets, personal data, transient details, or unverified assumptions. Keep the references and links current.

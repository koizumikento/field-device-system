# AGENTS.md

## Repository purpose

This repository organizes field and IoT device knowledge, design notes, and implementation assets by device.

- Use `devices/<device-name>/` as the main unit of organization.
- Keep reusable assets in `shared/` only when they are used by multiple devices.
- Use `experiments/` for temporary PoCs or trials.
- Use `archive/` for retired or superseded material.

## Preferred structure

Prefer a simple per-device layout.

```text
devices/
  <device-name>/
    README.md
    purpose.md
    requirements.md
    architecture.md
    operations.md
    diagrams/
    hardware/
    software/
    setup/
    tests/
```

## Documentation rules

- Prefer Markdown files for explanatory content such as purpose, requirements, architecture, and operations.
- Prefer folders only for collections of artifacts or implementation assets.
- Keep diagrams, wiring drawings, and system figures inside `diagrams/`.
- Do not split narrative content into many small folders unless there is a clear volume reason.
- Do not create empty directories unless content will be added in the same change.

## Naming conventions

- Use `kebab-case` for device names and directory names.
- Name device folders by the device itself, not by a broad theme.
- Keep file names predictable: `purpose.md`, `requirements.md`, `architecture.md`, `operations.md`.

## README expectations

Each device `README.md` should give the shortest useful entry point:

- what the device does
- where the main docs live
- current status
- key constraints or open issues

## Editing guidance

- Keep the repository practical and lightweight; avoid structure that produces many empty placeholders.
- When adding a new device, start with the minimum useful files and expand only when content appears.
- If code, CAD, or hardware assets are introduced, place them under the nearest device directory instead of a generic top-level folder.
- If a rule here stops matching the actual workflow, update this file rather than working around it repeatedly.
- For standard device scaffolding, prefer `scripts/create-device.sh <device-name>`.
- Use the repo-local skill `device-structure-manager` in `.agents/skills/` only when the task is not just a standard scaffold, such as normalizing an existing device directory.
- The standard scaffold templates live under `.agents/skills/device-structure-manager/assets/device-template/`.

## Validation

- This repository currently does not define a global build, lint, or test command.
- Do not invent toolchain commands in agent responses or docs.
- For documentation-only changes, verify file names, paths, and cross-references.
- If a device later gains an executable toolchain, document the exact commands in the nearest relevant `AGENTS.md` or `README.md`.

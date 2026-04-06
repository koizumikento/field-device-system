---
name: "device-structure-manager"
description: "Use when the user wants to normalize an existing device directory under `devices/`, or when the requested device setup goes beyond the standard scaffold handled by `scripts/create-device.sh`."
---

# Device Structure Manager

Normalize or extend a device workspace in this repository so it follows the repository's device-first structure without adding unnecessary placeholders.

Use this skill when the user needs:

- an existing device directory reorganized to match the repo conventions
- a device setup that differs from the standard scaffold
- a natural-language instruction layer on top of the standard scaffold process

## Do Not Use For

- plain standard scaffold creation when `scripts/create-device.sh` is enough
- broad repository restructuring outside `devices/`
- hardware or software implementation inside a device
- diagram authoring beyond creating the `diagrams/` location
- content-heavy technical writing that should be authored case by case

## Inputs

- device name
- whether the task is to normalize or extend
- any explicit files or folders to include or omit

## Repository standard

The default target layout is:

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
      bom.md
    software/
    setup/
    tests/
```

The canonical scaffold templates live under `assets/device-template/`.

## Workflow

1. Confirm the target device directory under `devices/`.
2. If the request is only standard scaffold creation, prefer `scripts/create-device.sh <device-name>` instead of manual work.
3. Check whether the device already exists and preserve any existing user content.
4. Create only the standard files and folders that are missing when the script does not already cover the task.
5. Keep explanatory content in Markdown files:
   - `README.md`
   - `purpose.md`
   - `requirements.md`
   - `architecture.md`
   - `operations.md`
   - `hardware/bom.md`
6. Keep artifact collections in folders:
   - `diagrams/`
   - `hardware/`
   - `software/`
   - `setup/`
   - `tests/`
7. If creating starter file content, keep it short and practical. Prefer headings and short placeholders over long templates.
8. Do not invent toolchains, component choices, test commands, or deployment steps that are not provided by the user or already present in the repo.
9. If the requested structure conflicts with the repository standard, follow the user request and then update `AGENTS.md` if the repository convention has clearly changed.

## Output expectations

- The target device directory exists under `devices/`.
- Missing standard files and folders are created.
- Existing user-authored content is preserved.
- The result stays lightweight and avoids empty structure beyond the standard device scaffold.

## Guardrails

- Use `kebab-case` for the device directory name unless the user explicitly asks otherwise.
- Name the directory after the device itself, not a broad theme.
- Keep diagrams in `diagrams/` rather than scattering them across docs folders.
- Do not create top-level `docs/` for device-specific content.
- Do not introduce extra nested structure unless the user asks for it or the content volume already justifies it.
- Prefer the existing template files in `assets/device-template/` instead of rewriting the same boilerplate.

## Stop conditions

- Stop if the user is asking for a repository-wide taxonomy redesign rather than a per-device scaffold.
- Stop if the requested target is not under `devices/` and the user has not explicitly changed that convention.

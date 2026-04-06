#!/bin/sh

set -eu

usage() {
  cat <<'EOF'
Usage:
  scripts/create-device.sh <device-name> [--dry-run]

Creates a new device directory under devices/ using the device-structure-manager skill assets.
It does not overwrite existing files.
EOF
}

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
  usage
  exit 1
fi

DEVICE_NAME="$1"
DRY_RUN=0

if [ "$#" -eq 2 ]; then
  if [ "$2" = "--dry-run" ]; then
    DRY_RUN=1
  else
    usage
    exit 1
  fi
fi

case "$DEVICE_NAME" in
  *[!a-z0-9-]*|'')
    echo "error: device name must be kebab-case (lowercase letters, numbers, hyphens)" >&2
    exit 1
    ;;
esac

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
TEMPLATE_DIR="$REPO_ROOT/.agents/skills/device-structure-manager/assets/device-template"
TARGET_DIR="$REPO_ROOT/devices/$DEVICE_NAME"

if [ ! -d "$TEMPLATE_DIR" ]; then
  echo "error: template directory not found: $TEMPLATE_DIR" >&2
  exit 1
fi

ensure_dir() {
  if [ -d "$1" ]; then
    return 0
  fi

  echo "mkdir -p $1"
  if [ "$DRY_RUN" -eq 0 ]; then
    mkdir -p "$1"
  fi
}

copy_template() {
  src="$1"
  dest="$2"

  if [ -e "$dest" ]; then
    echo "skip existing $dest"
    return 0
  fi

  echo "create $dest"
  if [ "$DRY_RUN" -eq 0 ]; then
    sed "s/<device-name>/$DEVICE_NAME/g" "$src" > "$dest"
  fi
}

ensure_dir "$TARGET_DIR"
ensure_dir "$TARGET_DIR/diagrams"
ensure_dir "$TARGET_DIR/hardware"
ensure_dir "$TARGET_DIR/software"
ensure_dir "$TARGET_DIR/setup"
ensure_dir "$TARGET_DIR/tests"

copy_template "$TEMPLATE_DIR/README.md" "$TARGET_DIR/README.md"
copy_template "$TEMPLATE_DIR/purpose.md" "$TARGET_DIR/purpose.md"
copy_template "$TEMPLATE_DIR/requirements.md" "$TARGET_DIR/requirements.md"
copy_template "$TEMPLATE_DIR/architecture.md" "$TARGET_DIR/architecture.md"
copy_template "$TEMPLATE_DIR/operations.md" "$TARGET_DIR/operations.md"

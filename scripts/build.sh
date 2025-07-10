#!/usr/bin/env bash
set -euo pipefail

# ── Parse flags ──────────────────────────────────────────────────────────
CLEAN_BUILD=0; CLEAN_LIB=0; CLEAN_APPS=0
show_help(){
  cat <<EOF
Usage: $0 [OPTIONS]
  --clean-build    Remove the build/ directory before building
  --clean-lib      Remove all files from /opt/robolib/lib before deploying
  --clean-apps     Remove all files from /opt/robolib/apps before deploying
  --clean-all      Do all of the above
  -h, --help       Show this help message and exit
EOF
  exit 0
}
while [[ $# -gt 0 ]]; do
  case $1 in
    --clean-build)   CLEAN_BUILD=1; shift;;
    --clean-lib)     CLEAN_LIB=1;   shift;;
    --clean-apps)    CLEAN_APPS=1;  shift;;
    --clean-all)     CLEAN_BUILD=1; CLEAN_LIB=1; CLEAN_APPS=1; shift;;
    -h|--help)       show_help;;
    *) echo "Unknown option: $1"; show_help;;
  esac
done

# ── Paths ───────────────────────────────────────────────────────────────
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &>/dev/null && pwd )"
PROJECT_ROOT="$( dirname "$SCRIPT_DIR" )"
BUILD_DIR="$PROJECT_ROOT/build"
LIB_DEST="/opt/robolib/lib"
APP_DEST="/opt/robolib/apps"

# ── Cleaning ────────────────────────────────────────────────────────────
(( CLEAN_BUILD )) && {
  echo "🧹 Cleaning build directory: $BUILD_DIR"
  rm -rf "$BUILD_DIR"
}
(( CLEAN_LIB )) && {
  echo "🧹 Cleaning shared-lib deploy dir: $LIB_DEST"
  sudo mkdir -p "$LIB_DEST"
  sudo rm -rf "${LIB_DEST:?}/"*
}
(( CLEAN_APPS )) && {
  echo "🧹 Cleaning apps deploy dir: $APP_DEST"
  sudo mkdir -p "$APP_DEST"
  sudo rm -rf "${APP_DEST:?}/"*
}

# ── 1) Configure ───────────────────────────────────────────────────────
echo "👉 Configuring in $BUILD_DIR"
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

# ── 2) Build ───────────────────────────────────────────────────────────
echo "👉 Building…"
cmake --build "$BUILD_DIR"

# ── 3) Deploy shared libraries (.so*) ──────────────────────────────────
echo "👉 Deploying shared libraries to $LIB_DEST"
sudo mkdir -p "$LIB_DEST"
shopt -s nullglob
for so in "$BUILD_DIR/lib/"*.so*; do
  echo "   → Copying $(basename "$so")"
  sudo cp -v "$so" "$LIB_DEST/"
done

# ── 4) Deploy executables → /opt/robolib/apps only ─────────────────────
echo "👉 Deploying executables to $APP_DEST"
sudo mkdir -p "$APP_DEST"
for exe in "$BUILD_DIR/bin/"*; do
  if [[ -f "$exe" && -x "$exe" ]]; then
    echo "   → Copying $(basename "$exe")"
    sudo cp -v "$exe" "$APP_DEST/"
  fi
done

echo "✅ Build + deploy complete!"

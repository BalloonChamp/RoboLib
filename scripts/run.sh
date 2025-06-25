#!/bin/bash
DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "$DIR" && pwd)
BUILD_DIR="$SCRIPT_DIR/../build"

if [ ! -f "$BUILD_DIR/robot" ]; then
    echo "Build not found. Run build.sh first." >&2
    exit 1
fi

"$BUILD_DIR/robot" "$@"

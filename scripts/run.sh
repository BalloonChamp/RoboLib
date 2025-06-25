#!/bin/bash
CONFIG=$1
if [ -z "$CONFIG" ]; then
  echo "Usage: $0 <config.json>" >&2
  exit 1
fi
DIR=$(dirname "$0")
"$DIR/../build/robot" "$CONFIG"

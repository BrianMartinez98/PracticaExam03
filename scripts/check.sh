#!/usr/bin/env bash
set -euo pipefail

CC=${CC:-gcc}
CFLAGS=${CFLAGS:-"-Wall -Wextra -Werror -std=c99"}
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

while IFS= read -r file; do
    out="$TMP_DIR/$(echo "$file" | tr '/ ' '__').o"
    echo "[check] $file"
    $CC $CFLAGS -D BUFFER_SIZE=42 -c "$file" -o "$out"
done < <(find . -type f -name '*.c' ! -path './build/*' ! -path './bin/*' | sort)

echo "All C files compile cleanly."

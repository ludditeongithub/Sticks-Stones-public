#!/usr/bin/env bash
set -euo pipefail

mkdir -p data/run

find world -mindepth 2 -maxdepth 2 -type f -name 'tables.hpp' -print0 |
while IFS= read -r -d '' src; do
    name="$(basename "$(dirname "$src")")"
    dest="data/const/${name}_tables.hpp"

    # Replace references to the old include path everywhere.
    grep -rlZ --exclude-dir=.git "world/${name}/tables.hpp" . |
        xargs -0 -r sed -i "s#world/${name}/data\.hpp#data/const/${name}_tables.hpp#g"

    # Move the file.
    mv -- "$src" "$dest"
done

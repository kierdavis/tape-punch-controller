#!/bin/sh

set -o errexit -o pipefail -o nounset

geda_dir=$(nix-build  --no-out-link '<nixpkgs>' -A geda)
sym_dir=$geda_dir/share/gEDA/sym
src=$(find $sym_dir -name "$1")
dest=$(dirname $0)/$2

if [ -z "$src" ]; then
  echo >&2 "No symbol named $1 found in $sym_dir"
  exit 1
fi

if [ $(echo "$src" | wc -l) -ne 1 ]; then
  echo >&2 "Multiple results found for $1:"
  echo >&2 "$src"
  exit 1
fi

cp -iv "$src" "$dest"
chmod 0644 "$dest"

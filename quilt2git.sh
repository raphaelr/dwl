#!/bin/sh
# creates a git branch for every patch
set -e
from=upstream/main
patches="tag-handling wlr_virtual_pointer_v1 wayland-ipc"
tmp="$(mktemp)"

headerof() {
    awk '/---/ { exit; } { print; }' "$1"
}

for patch in $patches; do
    fn="patches/${patch}.patch"
    echo "$fn"
    cp -f "$fn" "$tmp"
    git branch -f "$patch" "$from"
    git checkout "$patch"
    git apply --index "$tmp"
    make -B
    headerof "$tmp" | git commit -F -
    git checkout master
done

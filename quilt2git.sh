#!/bin/sh
# creates a git branch for every patch
set -e
from=master
patches="wlr_virtual_pointer_v1 wayland-ipc"

headerof() {
    awk '/---/ { exit; } { print; }' "$1"
}

git checkout master
for patch in $patches; do
    fn="patches/${patch}.patch"
    echo "$fn"
    git branch -f "$patch" "$from"
    git checkout "$patch"
    git apply --index "$fn"
    headerof "$fn" | git commit -F -
done
git checkout "$from"

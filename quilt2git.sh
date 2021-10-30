#!/bin/sh
# creates a git branch for every patch
set -e
from=upstream/main
patches="tag-handling master-on-right-toggle wlr_virtual_pointer_v1 wayland-ipc"
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
    patch -p1 --no-backup-if-mismatch -r - < "$tmp"
    make -B
    git add -A
    headerof "$tmp" | git commit -F -
    git reset --hard
    git checkout master
done

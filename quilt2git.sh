#!/bin/sh
# creates a git branch for every patch
set -e
from=upstream/main
tmp=$(mktemp)
trap 'rm "$tmp"' EXIT

status="$(git status -s)"
if [ -n "$status" ]; then
	echo "working directory is not clean!"
	git status
	exit 1;
fi

headerof() {
	awk '/---/ { exit; } { print; }' "$1"
}

series() {
	name="$1"
	echo "$name"
	git branch -f "$name" "$from"
	git checkout "$name"
	while shift && [ -n "$1" ]; do
		patch="$1"
		git show "master:patches/$patch.patch" > "$tmp"
		patch -p1 --no-backup-if-mismatch -r - < "$tmp"
		#make -B
		git add -A
		headerof "$tmp" | git commit -F -
	done
	git reset --hard
	git checkout master
}

single() {
	series "$1" "$1"
}

single layer-surface-performance
single tag-handling
single master-on-right-toggle
single wlr_virtual_pointer_v1
series wayland-ipc wayland-ipc-protocol wayland-ipc-control

#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

# Build & Run Unit Tests
printf "\n--- Build & Run Unit Tests\n"

readonly CURRENT_DIRECTORY="$(cd "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
source "${CURRENT_DIRECTORY}/scripts/config.sh"
source "${CURRENT_DIRECTORY}/scripts/util.sh"

# symlink CMakeList.txt
ln -sf CMakeListsBuild.txt CMakeLists.txt

mkdir -p build > /dev/null
pushd build > /dev/null

set echo off
FAILED="false"
cmake -quite ../. || (FAILED="true" && error "failed to configure project")
make -j 4 || (FAILED="true" && error "build failed")
popd > /dev/null


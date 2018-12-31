#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

# Build & Run Unit Tests
printf "\n--- Build & Run Unit Tests\n"

readonly CURRENT_DIRECTORY="$(cd "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
source "${CURRENT_DIRECTORY}/scripts/config.sh"
source "${CURRENT_DIRECTORY}/scripts/util.sh"

# symlink to build and test
ln -sf CMakeListsBuildAndTest.txt CMakeLists.txt

mkdir -p build/unit-tests > /dev/null
pushd build/unit-tests > /dev/null

set echo off
FAILED="false"
cmake -quite ../.. -DCMAKE_BUILD_TYPE=Coverage || (FAILED="true" && error "failed to configure project")
make coverage -j 4 || (FAILED="true" && error "build failed")
popd > /dev/null

if [[ "$FAILED" == "false" ]]; then
	python scripts/coverage_parser.py -i build/unit-tests/coverage/index.html
fi



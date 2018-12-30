#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

# Build & Run Unit Tests
printf "\n--- Build & Run Unit Tests\n"

mkdir -p build/unit-tests > /dev/null
pushd build/unit-tests > /dev/null

set echo off
cmake ../.. -DCMAKE_BUILD_TYPE=Coverage || echo "failed to configure project"
make coverage -j 4 || echo "build failed"
popd > /dev/null
python scripts/coverage_parser.py -i build/unit-tests/tests/coverage/index.html


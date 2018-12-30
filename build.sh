#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

# Build & Run Unit Tests
printf "\n--- Build & Run Unit Tests\n"

cmake . -DCMAKE_BUILD_TYPE=Coverage || echo "failed to configure project"
make -j 4 || echo"build failed"

pushd build/bin
./unit-tests  || error "unit test(s) failed"
popd


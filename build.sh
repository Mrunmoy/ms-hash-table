#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

# Build & Run Unit Tests
printf "\n--- Build & Run Unit Tests\n"

mkdir -p build/unit-tests > /dev/null
pushd build/unit-tests > /dev/null

set echo off
FAILED="false"
cmake -quite ../.. -DCMAKE_BUILD_TYPE=CCR || echo "failed to configure project" && FAILED="true"
make ccr -j 4 || echo "build failed" && FAILED="true"
popd > /dev/null

if [[ "$FAILED" == "false" ]]; then
	python scripts/coverage_parser.py -i build/unit-tests/ccr/index.html
fi



#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

readonly CURRENT_DIRECTORY="$(cd "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

source "${CURRENT_DIRECTORY}/scripts/config.sh"
source "${CURRENT_DIRECTORY}/scripts/util.sh"

# usage: build_image [tag]
build_image() {
  # Generate image name
  local name="${DOCKER_IMAGE_NAME}:$(arg_or_default "$1" \
                                                    "${DOCKER_IMAGE_TAG}")"

  print "building unit tests ${name}"

  # Run docker with the provided arguments
  docker build -t "${name}" \
                  "${CURRENT_DIRECTORY}/${DOCKER_LOCAL_SOURCE_DIRECTORY}"
}

# usage: main [-h] [-d DATA_DIRECTORY] [-t TAG] [ARGS...]
main() {
  check_requirements "$@" || exit 1

  # Docker build option
  if [ $1 ] && [ $1 == "--docker-build" ]; then
    docker-compose run --user=$CURRENT_UID hash-table-unit-tests ./build.sh
    exit
  fi
  build_image "$@"
}



# Build & Run Tests
printf "\n--- Build & Unit Tests\n"

mkdir -p cmake-build
pushd cmake-build

cmake ../ -DCMAKE_BUILD_TYPE=Coverage || err_log "failed \"cmake CMakeLists.txt\""
make Coverage -j || err_log "coverage failed"

printf "\n+++ Check Test Coverage\n"

# get coverage summary from index.html
cov=($(grep -oP -m 2 '("headerTableEntry" )[^ ]*' coverage/index.html | cut -d '>' -f2))

printf "\n${COLOR_GREEN}#############################${COLOR_RESET}\n"
printf "   Line Coverage: %.2f%%\n" ${cov[0]}
printf "   Branch Coverage: %.2f%%\n" ${cov[1]}
printf "${COLOR_GREEN}#############################${COLOR_RESET}\n"

printf "\n--- Build Complete\n"
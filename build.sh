#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

readonly CURRENT_DIRECTORY="$(cd "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
source "${CURRENT_DIRECTORY}/scripts/config.sh"
source "${CURRENT_DIRECTORY}/scripts/util.sh"

build_docker_image() {
  # Generate image name
  local name="${DOCKER_IMAGE_NAME}"
  print "--Building Docker Container ${name}"

  # Run docker with the provided arguments
  docker build -t "${name}" \
                  "${CURRENT_DIRECTORY}/${DOCKER_LOCAL_SOURCE_DIRECTORY}"
  docker run -t "${name}" ./build.sh
}

main() {
  check_requirements || exit 1

  if [[ $1 ]] && [[ $1 == "--use-docker" ]]; then
    build_docker_image
    exit
  fi

  # Build & Run Unit Tests
  printf "\n--- Build & Run Unit Tests\n"

  mkdir -p cmake-build
  pushd cmake-build

  cmake ../ -DCMAKE_BUILD_TYPE=Coverage || halt_build "failed \"cmake CMakeLists.txt\""
  make coverage -j || halt_build "build or test(s) failed"
}


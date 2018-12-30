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
  # Build & Run Unit Tests
  printf "\n--- Build & Run Unit Tests\n"

  cmake ../ -DCMAKE_BUILD_TYPE=Coverage || error "failed \"cmake CMakeLists.txt\""
  make coverage -j || error "build or test(s) failed"


}


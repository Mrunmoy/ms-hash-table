#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

# Color vars
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_YELLOW='\033[1;33m'
COLOR_RESET='\033[0m'


# usage: error [args...]
error() {
  printf "\n${COLOR_RED}error: $*${COLOR_RESET}\n" >&2
}

# usage: check_requirements
check_requirements() {
  which docker
  if [[ $? -eq 0 ]]; then
      docker --version | grep "Docker version"
      if [[ $? -eq 0 ]]; then
          echo "docker exists"
      else
          error "Docker not found! install docker"
          exit 1
      fi
  else
      error "Docker not found! install docker" >&2
      exit 1
  fi
}


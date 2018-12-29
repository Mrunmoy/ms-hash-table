#! /bin/bash

# Color vars
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_YELLOW='\033[1;33m'
COLOR_RESET='\033[0m'

# Err Log
function err_log()
{
 printf "\n${COLOR_RED}######################${COLOR_RESET}\n"
 printf "${COLOR_RED}# ${YELLOW}** Build failed ** ${RED}#\n"
 printf "${COLOR_RED}######################${COLOR_RESET}\n"
 printf "Error:${COLOR_RESET} %s\n" "$1"
 exit 1
}

# Docker build option
if [ $1 ] && [ $1 == "--docker-build" ]; then
  CURRENT_UID=$(id -u):$(id -g)
  docker-compose run --user=$CURRENT_UID unittests-env ./build.sh
  exit
fi

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
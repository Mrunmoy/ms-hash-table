#!/usr/bin/env bash

# Reference: https://codereview.stackexchange.com/questions/137877/shell-script-wrapper-for-docker-build-and-run

CURRENT_USER=$(whoami)
CURRENT_UID=$(id -u):$(id -g)

readonly DOCKER_IMAGE_NAME="${CURRENT_USER}/hash-table"
readonly DOCKER_IMAGE_TAG="0.1.0"
readonly DOCKER_IMAGE_MOUNT="~/docker/data"

readonly DOCKER_LOCAL_SOURCE_DIRECTORY="docker"
readonly DOCKER_LOCAL_MOUNT_DIRECTORY="data"
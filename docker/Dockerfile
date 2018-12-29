# Use an official gcc image as base
FROM gcc:7.3

# Install dependencies
RUN apt-get update
RUN apt-get install -y \
    gcovr \
    cmake

WORKDIR /workspace


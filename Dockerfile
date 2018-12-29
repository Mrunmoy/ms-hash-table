# Use an official gcc image as base
FROM gcc:7.3

# Install deps
RUN apt-get update && apt-get install -y \
    gcovr \
    cmake
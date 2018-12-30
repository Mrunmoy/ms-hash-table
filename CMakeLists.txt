cmake_minimum_required(VERSION 3.10)

# Project Name
project(hash_table C CXX)

# Compiler Standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Directories Settings
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_INSTALL_LIBDIR ${BUILD_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/scripts)

# Build Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
SET(CPP_PLATFORM Gcc)

include_directories(inc)

# build library for hash-table
add_library(hash-table
        src/hash_table.c)

# -- Unit Tests -- #
enable_testing()

# unit test build
if(testing_enabled)
    add_subdirectory(tests)
endif()

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

# unit test build
add_subdirectory(tests unit-tests)

# Code Coverage Check
if (CMAKE_BUILD_TYPE STREQUAL "CCR")
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    # message('----------------------')
    # message( ${PROJECT_SOURCE_DIR} )
    # message('----------------------')
    set(COVERAGE_GCOVR_EXCLUDES  '${PROJECT_SOURCE_DIR}/tests' '${PROJECT_SOURCE_DIR}/tests/dependencies')
    SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME ccr EXECUTABLE unit-tests DEPENDENCIES unit-tests )
endif()



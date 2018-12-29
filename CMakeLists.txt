cmake_minimum_required(VERSION 3.10)

# Project Name
project(hash_table C CXX)

IF (WIN32)
    # set stuff for windows
ELSE()
    find_package(Threads REQUIRED)
    find_library(LIBRT rt)
ENDIF()

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

# Preprocessor Definitions
add_definitions(-DUNIT_TEST=1)

# Build Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

# add cpputest library
SET(CppUTestRootDirectory ${PROJECT_SOURCE_DIR}/dependencies/ms-cpputest)
SET(CPP_PLATFORM Gcc)
add_subdirectory(${CppUTestRootDirectory}/src/CppUTest CppUTest)
add_subdirectory(${CppUTestRootDirectory}/src/CppUTestExt CppUTestExt)

# Include directories for header files
include_directories(inc
        ${CppUTestRootDirectory}/include)

# build library for hash-table
add_library(hash-table
        src/hash_table.c)

# Unit Test executable
add_executable(unit-tests tests/AllTests.cpp tests/TestHashTable.cpp)

# Link all the binaries/libraries to build the executable

IF (WIN32)
    # set stuff for windows
ELSE()
    target_link_libraries(unit-tests hash-table CppUTest CppUTestExt ${LIBRT})
ENDIF()

# Code Coverage Check
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    set(COVERAGE_GCOVR_EXCLUDES '${PROJECT_SOURCE_DIR}/tests' '${PROJECT_SOURCE_DIR}/dependencies')
    SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME coverage EXECUTABLE unit-tests DEPENDENCIES unit-tests --print-summary)
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

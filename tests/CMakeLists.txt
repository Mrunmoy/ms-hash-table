cmake_minimum_required(VERSION 3.10)

# Project Name
project(unit-tests C CXX)

IF (WIN32)
    # set stuff for windows
ELSE()
    find_package(Threads REQUIRED)
    find_library(LIBRT rt)
ENDIF()

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/inc
        )

# Compiler Standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# add cpputest library
SET(CppUTestRootDirectory ${PROJECT_SOURCE_DIR}/dependencies/ms-cpputest)
SET(CPP_PLATFORM Gcc)
add_subdirectory(${CppUTestRootDirectory})

include_directories(inc
        ${CppUTestRootDirectory}/include)

# Unit Test executable

add_executable(${PROJECT_NAME} tests/AllTests.cpp tests/TestHashTable.cpp)

# Link all the binaries/libraries to build the executable

IF (WIN32)
    # set stuff for windows
ELSE()
    # Link the static library from subproject1 using it's alias sub::lib1
    # Link the header only library from subproject2 using it's alias sub::lib2
    # This will cause the include directories for that target to be added to this project
    target_link_libraries(${PROJECT_NAME}
            hash-table
            CppUTest
            CppUTestExt
            ${LIBRT}
            )
ENDIF()

# Code Coverage Check
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    set(COVERAGE_GCOVR_EXCLUDES '${PROJECT_SOURCE_DIR}/tests' '${PROJECT_SOURCE_DIR}/dependencies')
    SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME coverage EXECUTABLE unit-tests DEPENDENCIES unit-tests --print-summary)
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

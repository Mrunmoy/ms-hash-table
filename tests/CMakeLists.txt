cmake_minimum_required(VERSION 3.10)

# Project Name
project(unit-tests C CXX)

if (WIN32)
    # set stuff for windows
else()
    find_package(Threads REQUIRED)
    find_library(LIBRT rt)
endif()

include_directories(${PROJECT_SOURCE_DIR}/inc)

# Directories Settings
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_INSTALL_LIBDIR ${BUILD_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/scripts)

# message( "-------------------" )
# message( ${CMAKE_SOURCE_DIR} )
# message( "-------------------" )

# Build Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
SET(CPP_PLATFORM Gcc)

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
# build library for hash-table
add_library(hash-table-lib
        ../src/hash_table.c)

add_executable(${PROJECT_NAME} AllTests.cpp TestHashTable.cpp)

# Link all the binaries/libraries to build the executable

if (WIN32)
    # set stuff for windows
else()
    # Link the static library from subproject1 using it's alias sub::lib1
    # Link the header only library from subproject2 using it's alias sub::lib2
    # This will cause the include directories for that target to be added to this project
    target_link_libraries(${PROJECT_NAME}
            hash-table-lib
            CppUTest
            CppUTestExt
            ${LIBRT}
            )
endif()

# Code Coverage Check
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS() 
    set(COVERAGE_GCOVR_EXCLUDES '.' '${PROJECT_SOURCE_DIR}/dependencies')
    SETUP_TARGET_FOR_COVERAGE_GCOVR_XML(NAME xml_coverage EXECUTABLE ${PROJECT_NAME} DEPENDENCIES ${PROJECT_NAME} )
    SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(NAME coverage EXECUTABLE ${PROJECT_NAME} DEPENDENCIES ${PROJECT_NAME} )
endif()


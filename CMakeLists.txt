cmake_minimum_required(VERSION 3.12)
project(hash_table C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(hash_table src/hash_table.c src/test.c)
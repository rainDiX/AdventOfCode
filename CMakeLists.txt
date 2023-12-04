cmake_minimum_required(VERSION 3.25)

project(AdventOfCode 
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "compiler is ${CMAKE_CXX_COMPILER_ID}")

# Clang does not fully support concepts and so it can't use std::expected with libstdc++
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options("-stdlib=libc++")
  add_link_options("-stdlib=libc++")
  add_link_options("-lc++abi")
endif()

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No CMAKE_BUILD_TYPE specified, default to Release.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(common)
add_subdirectory(Day1)
add_subdirectory(Day2)
add_subdirectory(Day3)
add_subdirectory(Day4)
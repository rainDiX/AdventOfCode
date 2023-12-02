cmake_minimum_required(VERSION 3.25)

project(AdventOfCode 
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No CMAKE_BUILD_TYPE specified, default to Release.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(Day1)
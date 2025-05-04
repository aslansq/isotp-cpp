# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

set(prj_name "isotp")

# Project name and language
project(${prj_name} LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library
add_library(${prj_name} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/isotp.cpp)

# Include directories
target_include_directories(${prj_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add any necessary compiler options or definitions
target_compile_options(${prj_name} PRIVATE -Wall -Wextra)
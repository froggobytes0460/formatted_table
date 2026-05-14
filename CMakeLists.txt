cmake_minimum_required(VERSION 3.10)
project(formatted_table LANGUAGES CXX)

# Create the .gitignore instantly inside the build folder
if(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/.gitignore" "*\n")
endif()

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files for compilation
set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})
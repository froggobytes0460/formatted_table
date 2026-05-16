cmake_minimum_required(VERSION 3.10)
project(formatted_table LANGUAGES CXX)

enable_testing() # At the very top to make CMake registers add_test() macros properly

include(FetchContent)

# Create the .gitignore instantly inside the build folder
if(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/.gitignore" "*\n")
endif()

# Fetch the fmt library from GitHub.
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.0.2
  SYSTEM
)

# Fetch the argparse library from GitHub.
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG v3.2
  SYSTEM
)

# Fetch testing framework
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
    SYSTEM
)

# Make the libraries available for linking.
FetchContent_MakeAvailable(fmt argparse catch2)

# Create a library with the core functionality
add_library(formatted-table-lib people.cpp)
target_include_directories(formatted-table-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(formatted-table-lib PUBLIC fmt::fmt argparse)
target_compile_features(formatted-table-lib PUBLIC cxx_std_20)

set(SOURCE_FILES
    main.cpp
    people.cpp
    include/people.hpp
)


# Add source files for compilation.
add_executable(formatted-table ${SOURCE_FILES})
target_link_libraries(formatted-table PRIVATE formatted-table-lib)

# Testing setup
add_executable(tests test/test_people.cpp)
target_link_libraries(tests PRIVATE formatted-table-lib Catch2::Catch2WithMain)
add_test(NAME all_tests COMMAND tests)

set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy;"
    "-checks=bugprone-*,modernize-*,performance-*;"
    "-header-filter=${CMAKE_CURRENT_SOURCE_DIR}/include/;"
    "-system-headers=false;"
    "--quiet"
)

# MacOS optimization.
if(APPLE)
    add_custom_command(TARGET formatted-table POST_BUILD
        COMMAND codesign --force --sign - $<TARGET_FILE:formatted-table>
        COMMENT "MACOS: Applying ad-hoc code signature to bypass Gatekeeper scan"
    )
endif()

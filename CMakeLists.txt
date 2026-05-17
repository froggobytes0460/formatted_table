cmake_minimum_required(VERSION 3.10)
project(formatted_table LANGUAGES CXX)

include(FetchContent)

# Create the .gitignore instantly inside the build folder
if(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/.gitignore" "*\n")
endif()

# Fetch dependencies
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.0.2
  SYSTEM
)

FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG v3.2
  SYSTEM
)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
    SYSTEM
)

FetchContent_MakeAvailable(fmt argparse catch2)

# Core Library Target
enable_testing()
add_library(formatted-table-lib people.cpp)
target_include_directories(formatted-table-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(formatted-table-lib PUBLIC fmt::fmt argparse)
target_compile_features(formatted-table-lib PUBLIC cxx_std_20)

# Main Executable Target
add_executable(formatted-table main.cpp)
target_link_libraries(formatted-table PRIVATE formatted-table-lib)

# Testing setup
add_executable(tests test/test_people.cpp)
target_link_libraries(tests PRIVATE formatted-table-lib Catch2::Catch2WithMain)
add_test(NAME all_tests COMMAND tests)

# MacOS optimization.
if(APPLE)
    add_custom_command(TARGET formatted-table POST_BUILD
        COMMAND codesign --force --sign - $<TARGET_FILE:formatted-table>
        COMMENT "MACOS: Applying ad-hoc code signature to bypass Gatekeeper scan"
    )
endif()

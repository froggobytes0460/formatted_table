cmake_minimum_required(VERSION 3.10)
project(formatted_table LANGUAGES CXX)

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
)

FetchContent_MakeAvailable(fmt)

# Fetch the argparse library from GitHub.
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG v3.2
)

FetchContent_MakeAvailable(argparse)

# Add source files for compilation.
set(SOURCE_FILES main.cpp people.cpp)
add_executable(main ${SOURCE_FILES})

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE fmt argparse)
target_compile_features(main PRIVATE cxx_std_20)

# For Macos, speeding up first run
if(APPLE)
    add_custom_command(TARGET main POST_BUILD
        COMMAND codesign --force --sign - $<TARGET_FILE:main>
        COMMENT "MACOS: Applying ad-hoc code signature to bypass Gatekeeper scan"
    )
endif()
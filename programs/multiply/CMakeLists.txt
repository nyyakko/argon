cmake_minimum_required(VERSION 3.5)
project(multiply LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

include(static_analyzers)

# set(multiply_LinkerOptions ${multiply_LinkerOptions}
# )

set(multiply_CompilerOptions ${multiply_CompilerOptions}
    -m32
    -ffreestanding
    -nostdlib
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wcast-align
    -Wunused
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
)

# find_package(package CONFIG REQUIRED)
# . . .
#
# set(multiply_ExternalLibraries)

add_subdirectory(multiply)

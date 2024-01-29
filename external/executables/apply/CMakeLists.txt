cmake_minimum_required(VERSION 3.5)
project(apply LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

include(static_analyzers)

# set(apply_LinkerOptions ${apply_LinkerOptions}
# )

set(apply_CompilerOptions ${apply_CompilerOptions}
    -fno-pie
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
# set(apply_ExternalLibraries)

add_subdirectory(apply)

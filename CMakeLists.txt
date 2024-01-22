cmake_minimum_required(VERSION 3.5)
project(argon LANGUAGES CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})

include(static_analyzers)
include(toolchain_vcpkg)
include(remote_clone)

# enable_vcpkg()

# set(argon_LinkerOptions ${argon_LinkerOptions}
# )

set(argon_CompilerOptions ${argon_CompilerOptions}
    --target=i686-pc-unknown-elf
    -march=i686
    -ffreestanding
    -fno-exceptions
    -fno-threadsafe-statics
    -fno-rtti
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
)

# find_package(package CONFIG REQUIRED)
# set(argon_ExternalLibraries)

add_subdirectory(argon)

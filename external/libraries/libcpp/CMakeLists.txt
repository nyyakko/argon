cmake_minimum_required(VERSION 3.5)
project(libcpp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(EXPORT_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake")
set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})

include(static_analyzers)
include(enable_vcpkg)
include(remote_clone)
include(enable_tests)
include(GNUInstallDirs)

# enable_vcpkg()
# enable_tests()

# set(libcpp_LinkerOptions ${libcpp_LinkerOptions}
#   . . .
# )

set(libcpp_CompilerOptions ${libcpp_CompilerOptions}
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
# . . .
#
# set(arser_ExternalLibraries package ...)

add_subdirectory(libcpp)


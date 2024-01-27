add_subdirectory(source)

add_library(kernel STATIC "${argon_SourceFiles}")

set(CMAKE_ASM_FLAGS "-x assembler-with-cpp")

set_target_properties(kernel PROPERTIES PREFIX "")
set_target_properties(kernel PROPERTIES SUFFIX ".img.a")

enable_static_analyzers(kernel ON)

target_include_directories(kernel
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/argon"
)

target_compile_features(kernel PRIVATE cxx_std_23)

target_link_options(kernel PRIVATE ${argon_LinkerOptions})
target_compile_options(kernel PRIVATE ${argon_CompilerOptions})
target_link_libraries(kernel PRIVATE ${argon_ExternalLibraries} libc libcpp)

add_custom_command(TARGET kernel
    POST_BUILD
        COMMAND ld
            -T ${CMAKE_CURRENT_SOURCE_DIR}/source/linker.ld
            -o ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/kernel.img
            -m elf_i386
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/kernel.img.a
)


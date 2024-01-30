add_subdirectory(source)

add_library(${PROJECT_NAME} STATIC "${validator_SourceFiles}")

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".bin.a")

enable_static_analyzers(${PROJECT_NAME} ON)

target_include_directories(${PROJECT_NAME} 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" 
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/validator"
)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_23)

target_link_options(${PROJECT_NAME} PRIVATE ${validator_LinkerOptions})
target_compile_options(${PROJECT_NAME} PRIVATE ${validator_CompilerOptions})
target_link_libraries(${PROJECT_NAME} PRIVATE ${validator_ExternalLibraries})

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
        COMMAND ld
            -T ${CMAKE_CURRENT_SOURCE_DIR}/source/linker.ld
            -o ${CMAKE_SOURCE_DIR}/iso/modules/${PROJECT_NAME}
            -m elf_i386
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/validator.bin.a
)



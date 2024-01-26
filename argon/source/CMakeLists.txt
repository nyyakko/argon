add_subdirectory(hardware)
add_subdirectory(descriptor)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_SourceFiles ${argon_SourceFiles}
    "${DIR}/Panic.cpp"
    "${DIR}/Terminal.cpp"
    "${DIR}/boot.s"
    "${DIR}/kmain.cpp"

    PARENT_SCOPE
)

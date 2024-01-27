add_subdirectory(descriptor)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_SourceFiles ${argon_SourceFiles}
    "${DIR}/Panic.cpp"

    PARENT_SCOPE
)


add_subdirectory(hid)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_SourceFiles ${argon_SourceFiles}
    "${DIR}/VGA.cpp"
    "${DIR}/IO.cpp"

    PARENT_SCOPE
)

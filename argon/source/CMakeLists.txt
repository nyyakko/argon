set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_SourceFiles ${argon_SourceFiles}
    "${DIR}/loadgdt.s"
    "${DIR}/kmain.cpp"
    "${DIR}/boot.s"

    PARENT_SCOPE
)

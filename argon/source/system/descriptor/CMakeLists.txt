add_subdirectory(handling)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_SourceFiles ${argon_SourceFiles}
    "${DIR}/GDT.cpp"
    "${DIR}/GDT.s"
    "${DIR}/IDT.cpp"
    "${DIR}/IDT.s"

    PARENT_SCOPE
)

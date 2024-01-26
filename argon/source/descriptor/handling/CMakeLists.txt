set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_SourceFiles ${argon_SourceFiles}
    "${DIR}/IRQ.cpp"
    "${DIR}/IRQ.s"
    "${DIR}/ISR.cpp"
    "${DIR}/ISR.s"

    PARENT_SCOPE
)

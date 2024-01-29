add_subdirectory(handling)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_HeaderFiles ${argon_HeaderFiles}
    "${DIR}/GDT.hpp"
    "${DIR}/IDT.hpp"

    PARENT_SCOPE
)

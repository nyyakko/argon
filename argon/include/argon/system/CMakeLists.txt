add_subdirectory(descriptor)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_HeaderFiles ${argon_HeaderFiles}
    "${DIR}/Panic.hpp"

    PARENT_SCOPE
)

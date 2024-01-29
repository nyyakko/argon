add_subdirectory(hardware)
add_subdirectory(system)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_HeaderFiles ${argon_HeaderFiles}
    "${DIR}/Terminal.hpp"

    PARENT_SCOPE
)

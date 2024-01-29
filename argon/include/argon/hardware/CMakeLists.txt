add_subdirectory(hid)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(argon_HeaderFiles ${argon_HeaderFiles}
    "${DIR}/VGAEntry.hpp"
    "${DIR}/VGAColor.hpp"
    "${DIR}/VGA.hpp"
    "${DIR}/MultiBoot.hpp"
    "${DIR}/IO.hpp"

    PARENT_SCOPE
)

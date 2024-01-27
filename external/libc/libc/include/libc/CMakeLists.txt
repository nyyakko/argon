set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(libc_HeaderFiles ${libc_HeaderFiles}
    "${DIR}/string.hpp"
    "${DIR}/random.hpp"

    PARENT_SCOPE
)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(libc_HeaderFiles ${libc_HeaderFiles}
    "${DIR}/strlen.hpp"
    "${DIR}/strcmp.hpp"
    "${DIR}/string.hpp"
    "${DIR}/memset.hpp"
    "${DIR}/random.hpp"

    PARENT_SCOPE
)

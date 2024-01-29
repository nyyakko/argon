add_subdirectory(conversion)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(libcpp_HeaderFiles ${libcpp_HeaderFiles}
    "${DIR}/Iota.hpp"
    "${DIR}/Numerical.hpp"
    "${DIR}/Pair.hpp"
    "${DIR}/Array.hpp"
    "${DIR}/StringView.hpp"

    PARENT_SCOPE
)

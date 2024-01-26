#pragma once

#include <stddef.h>

template <class To>
constexpr auto bit_cast(auto const& source)
{
    To destination {};
    __builtin_memcpy(&destination, &source, sizeof(To));
    return destination;
}

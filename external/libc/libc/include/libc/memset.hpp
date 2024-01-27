#pragma once

#include <stddef.h>

namespace libc {

constexpr auto memset(auto* destination, auto const byte, size_t const count)
{
    for (auto index = 0u; index != count; index += 1)
    {
        destination[index] = byte;
    }
}

}
